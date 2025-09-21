import heapq

MOVES = [(0, 1), (0, -1), (1, 0), (-1, 0)]

def cal_mispalced_tiles(mat, goal_state):
  misplaced = 0
  for r in range(3):
    for c in range(3):
      if mat[r][c] != 0 and mat[r][c] != goal_state[r][c]:
        misplaced += 1
  return misplaced

def cal_manhattan_distance(mat, goal_state):
  distance = 0
  goal_pos = {}

  for r in range(3):
    for c in range(3):
      goal_pos[goal_state[r][c]] = (r, c)
  
  for r in range(3):
    for c in range(3):
      tile = mat[r][c]
      if tile != 0:
        goal_r, goal_c = goal_pos[tile]
        distance += abs(r - goal_r) + abs(c - goal_c)
  return distance

def zero_pos(mat):
  for r in range(3):
    for c in range(3):
      if mat[r][c] == 0:
        return r, c
  return None, None
      
def input_puzzle(args):
  print(args)
  puzzle = []

  for i in range(3):
    while True:
      row_str = input(f"Masukan 3 angka untuk baris {i + 1} (dipisah spasi): ")
      try:
        row = [int(num) for num in row_str.split()]
        if len(row) == 3:
          puzzle.append(row)
          break
        else:
          print("Error: Harap masukkan 3 angka!")
      except ValueError:
        print("Error: Masukkan hanya berupa angka yang valid!")
  return puzzle

def solve_puzzle_best_first(mat, goal_state):
  goal_state_tuple = tuple(map(tuple, goal_state))
  zero_y, zero_x = zero_pos(mat)

  # Deklarasi priority queue
  pq = [(cal_mispalced_tiles(mat, goal_state), mat, zero_y, zero_x)]

  # Deklarasi DSA Path Maping, Visited, dan Tuple
  mat_tuple = tuple(map(tuple, mat))
  visited = {mat_tuple}
  parent = {mat_tuple: None}

  move_count = 0
  while pq:
    h, cur_mat, cur_y, cur_x = heapq.heappop(pq)
    cur_mat_tuple = tuple(map(tuple, cur_mat))
    move_count += 1;

    # Jika ketemu solusi
    if cur_mat_tuple == goal_state_tuple:
      print(f"\nSolusi Best_First ditemukan setelah memeriksa {move_count} keadaan!")

      # Backtracking path
      path, node = [], cur_mat_tuple
      while node is not None:
        path.append(node)
        node = parent[node]
      path.reverse()

      # Print Path
      print(f"Jumlah langkah (Actual Cost): {len(path) - 1}")
      for i, mat_path in enumerate(path):
        print(f"\nLangkah {i}:")
        for row in mat_path:
          print(row)
      return
    
    for dy, dx in MOVES:
      new_y, new_x = cur_y + dy, cur_x + dx

      if 0 <= new_y < 3 and 0 <= new_x < 3:
        # Copy
        new_mat = [row[:] for row in cur_mat]

        # Swap 
        new_mat[cur_y][cur_x], new_mat[new_y][new_x] = new_mat[new_y][new_x], new_mat[cur_y][cur_x]

        # Buat Tuple (Optimasi) (Opsional)
        new_mat_tuple = tuple(map(tuple, new_mat))

        # Menambahkan visited dan Push PQ
        if new_mat_tuple not in visited:
          visited.add(new_mat_tuple)
          parent[new_mat_tuple] = cur_mat_tuple
          new_heuristic = cal_mispalced_tiles(new_mat, goal_state)
          heapq.heappush(pq, (new_heuristic, new_mat, new_y, new_x))

def solve_puzzle_A_star(mat, goal_state):
  goal_state_tuple = tuple(map(tuple, goal_state))
  zero_y, zero_x = zero_pos(mat)
  
  # Priority queue: (f_score, g_score, matrix, y_kosong, x_kosong)
  pq = [(cal_manhattan_distance(mat, goal_state), 0, mat, zero_y, zero_x)]

  mat_tuple = tuple(map(tuple, mat))
  visited = {mat_tuple}
  parent = {mat_tuple: None}

  move_count = 0
  while pq:
    cur_f, cur_g, cur_mat, cur_y, cur_x = heapq.heappop(pq)
    cur_mat_tuple = tuple(map(tuple, cur_mat))
    move_count += 1

    if cur_mat_tuple == goal_state_tuple:
      print(f"\nSolusi A* ditemukan setelah memeriksa {move_count} keadaan!")

      path, node = [], cur_mat_tuple
      while node is not None:
        path.append(node)
        node = parent[node]
      path.reverse()

      print(f"Jumlah langkah (Actual Cost): {len(path) - 1}")
      for i, mat_path in enumerate(path):
        print(f"\nLangkah {i}:")
        for row in mat_path:
          print(row)
      return
    
    for dy, dx in MOVES:
      new_y, new_x = cur_y + dy, cur_x + dx

      if 0 <= new_y < 3 and 0 <= new_x < 3:
        # Copy
        new_mat = [row[:] for row in cur_mat]

        # Swap
        new_mat[cur_y][cur_x], new_mat[new_y][new_x] = new_mat[new_y][new_x], new_mat[cur_y][cur_x]

        # Buat Tuple (Optimasi) (Opsional)
        new_mat_tuple = tuple(map(tuple, new_mat))

        # Menambahkan visited dan Push PQ
        if new_mat_tuple not in visited:
          visited.add(new_mat_tuple)
          parent[new_mat_tuple] = cur_mat_tuple

          new_g = cur_g + 1
          new_h = cal_manhattan_distance(new_mat, goal_state)
          new_f = new_g + new_h

          heapq.heappush(pq, (new_f, new_g, new_mat, new_y, new_x))

if __name__ == "__main__":

  # Bagian Kosong dari puzzle diisi dengan 0
  print("Pada saat input Keadaan Awal/Akhir Puzzle, bagian yang kosong harap diisi dengan angka 0 dan tolong jangan menginput duplikasi!")

  start_state = input_puzzle("\n--> Masukkan Keadaan Awal Puzzle <--")

  goal_state = input_puzzle("\n--> Masukkan Keadaan Akhir Puzzle <--")
  
  print("\n--> Menggunakan algoritma Best-First Search <--")
  solve_puzzle_best_first(start_state, goal_state)

  print("\n--> Menggunakan algoritma A* Search <--")
  solve_puzzle_A_star(start_state, goal_state)
