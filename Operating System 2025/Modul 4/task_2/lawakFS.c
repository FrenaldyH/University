#define _DEFAULT_SOURCE
#define FUSE_USE_VERSION 28
#include <fuse.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <dirent.h>
#include <errno.h>
#include <sys/time.h>

static const char *source_dir = "/home/fren/task_2/sumber";

static void find_real_path(char fpath[1000], const char *path) {
    char temp_path[1000];   
    sprintf(temp_path, "%s%s", source_dir, path);

    struct stat st;
    if (lstat(temp_path, &st) == 0 && S_ISDIR(st.st_mode)) {
        strcpy(fpath, temp_path);
        return;
    }

    char parent_path[1000];
    char *last_slash = strrchr(path, '/');
    if (last_slash == NULL) {
        strcpy(parent_path, "/");
    } else {
        strncpy(parent_path, path, last_slash - path + 1);
        parent_path[last_slash - path + 1] = '\0';
    }
    
    char source_parent_path[1000];
    sprintf(source_parent_path, "%s%s", source_dir, parent_path);

    char *short_name = (last_slash == NULL) ? (char*)path : last_slash + 1;
    
    DIR *dp = opendir(source_parent_path);
    if (dp == NULL) {
        strcpy(fpath, temp_path);
        return;
    }

    struct dirent *de;
    int found = 0;
    while ((de = readdir(dp)) != NULL) {
        if (de->d_type == DT_REG) {
            char real_name_base[256];
            strcpy(real_name_base, de->d_name);
            char *last_dot = strrchr(real_name_base, '.');
            if (last_dot != NULL) {
                *last_dot = '\0';
            }

            if (strcmp(short_name, real_name_base) == 0) {
                sprintf(fpath, "%s%s", source_parent_path, de->d_name);
                found = 1;
                break;
            }
        }
    }
    closedir(dp);

    if (!found) {
        strcpy(fpath, temp_path);
    }
}

static int lawak_mkdir(const char *path, mode_t mode) { return -EROFS; }
static int lawak_rmdir(const char *path) { return -EROFS; }
static int lawak_unlink(const char *path) { return -EROFS; }
static int lawak_write(const char *path, const char *buf, size_t size, off_t offset, struct fuse_file_info *fi) { return -EROFS; }
static int lawak_rename(const char *from, const char *to) { return -EROFS; }
static int lawak_truncate(const char *path, off_t size) { return -EROFS; }
static int lawak_create(const char *path, mode_t mode, struct fuse_file_info *fi) { return -EROFS; }

static int is_secret_and_access_denied(const char *path) {
    char *path_basename = strrchr(path, '/');
    if (path_basename == NULL) {
        path_basename = (char*)path;
    } else {
        path_basename++;
    }

    char name_without_ext[256];
    strcpy(name_without_ext, path_basename);

    char *last_dot = strrchr(name_without_ext, '.');
    if (last_dot != NULL) {
        *last_dot = '\0';
    }

    if (strcmp(name_without_ext, "secret") == 0) {
        time_t now;
        struct tm *local_time;
        time(&now);
        local_time = localtime(&now);
        int current_hour = local_time->tm_hour;

        if (current_hour < 8 || current_hour >= 18) {
            return 1; 
        }
    }

    return 0; 
}

static int lawak_getattr(const char *path, struct stat *stbuf) {
    if (is_secret_and_access_denied(path)) {
        return -ENOENT;
    }

    int res;
    char fpath[1000];
    find_real_path(fpath, path);

    res = lstat(fpath, stbuf);
    if (res == -1) return -errno;
    return 0;
}

static int lawak_readdir(const char *path, void *buf, fuse_fill_dir_t filler, off_t offset, struct fuse_file_info *fi) {
    (void) offset;
    (void) fi;
    char fpath[1000];
    
    sprintf(fpath, "%s%s", source_dir, path);

    DIR *dp = opendir(fpath);
    if (dp == NULL) return -errno;

    struct dirent *de;
    while ((de = readdir(dp)) != NULL) {
        char entry_path[1000];
        sprintf(entry_path, "%s%s%s", path, strcmp(path, "/") == 0 ? "" : "/", de->d_name);

        if (is_secret_and_access_denied(entry_path)) {
            continue; 
        }

        if (de->d_type == DT_REG) { 
            char file_name[256];
            strcpy(file_name, de->d_name); 
            char *last_dot = strrchr(file_name, '.'); 
            if (last_dot != NULL) *last_dot = '\0'; 
            if (filler(buf, file_name, NULL, 0) != 0) break;
        } else { 
            if (filler(buf, de->d_name, NULL, 0) != 0) break;
        }
    }
    closedir(dp);
    return 0;
}

static int lawak_read(const char *path, char *buf, size_t size, off_t offset, struct fuse_file_info *fi) {
    (void) fi;
    int res;
    char fpath[1000];
    find_real_path(fpath, path);

    int fd = open(fpath, O_RDONLY);
    if (fd == -1) return -errno;

    res = pread(fd, buf, size, offset);
    if (res == -1) res = -errno;

    close(fd);
    return res;
}

static int lawak_open(const char *path, struct fuse_file_info *fi) {
    char fpath[1000];
    find_real_path(fpath, path);
    return 0;
}

static int lawak_access(const char *path, int mask) {
    if (is_secret_and_access_denied(path)) {
        return -ENOENT;
    }

    char fpath[1000];
    find_real_path(fpath, path);
    return 0;
}

static struct fuse_operations lawak_oper = {
    .getattr = lawak_getattr,
    .readdir = lawak_readdir,
    .read = lawak_read,
    .open = lawak_open,
    .access = lawak_access,
    .mkdir = lawak_mkdir,
    .rmdir = lawak_rmdir,
    .unlink = lawak_unlink,
    .write = lawak_write,
    .rename = lawak_rename,
    .truncate = lawak_truncate,
    .create = lawak_create,
};

int main(int argc, char *argv[]) {
    umask(0);
    return fuse_main(argc, argv, &lawak_oper, NULL);
}
