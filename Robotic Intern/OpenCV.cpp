#include <iostream>
#include <ctime>
#include <cstdlib>
#include <opencv4/opencv2/opencv.hpp>

using namespace std;
using namespace cv;

struct HSVT {
    int hmin, smin, vmin, hmax, smax, vmax;
};

class Game {
private:
    Mat f; // Frame
    Size fS; // Frame Size
    VideoCapture cap; // Capture
    Point candy, keranjang;
    int score, r_candy, r_keranjang;
    bool d; // Direction of candy

public:
    Game() : cap(0), score(0), r_candy(15), r_keranjang(20), d(false) {
        if (!cap.isOpened()) {
            cerr << "Unable to open camera!" << endl;
            exit(EXIT_FAILURE);
        }
        cap.read(f);
        fS = f.size();
        srand(static_cast<unsigned int>(time(nullptr)));
        spawnCandy();
    }

    //Spawn candy .....
    void spawnCandy() {
        candy = Point(rand() % (fS.width - 2 * r_candy) + r_candy, 0);
        d = rand() % 2 == 0;  // biar arah munculnya random
    }


    void play() {
        Mat hsv, limc;
        HSVT det {0, 100, 100, 10, 255, 255};

        while (true) {
            cap >> f;
            if (f.empty()) break;

            cvtColor(f, hsv, COLOR_BGR2HSV);
            inRange(hsv, Scalar(det.hmin, det.smin, det.vmin), Scalar(det.hmax, det.smax, det.vmax), limc);

            vector<vector<Point>> contours;
            findContours(limc, contours, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);

            // Bagian Contour // Jujur ini bagian paling susah menurutku + minta bantuan kawan
            if (!contours.empty()) {
                int largestIndex = max_element(contours.begin(), contours.end(), 
                    [](const vector<Point>& a, const vector<Point>& b) {
                        return contourArea(a) < contourArea(b);
                    }) - contours.begin();

                Moments m = moments(contours[largestIndex]);
                if (m.m00 != 0) {
                    keranjang = Point(m.m10 / m.m00, m.m01 / m.m00);
                    r_keranjang = static_cast<int>(sqrt(contourArea(contours[largestIndex]) / M_PI));
                }
            }

            // Gerakin candynya
            candy.y += 10;
            candy.x += d ? 20 : -20;

            // Tul mantul kalo kena dinding
            if (candy.x <= r_candy || candy.x >= fS.width - r_candy) {
                d = !d;
            }

            // Munculin candy lagi 
            if (candy.y > fS.height) spawnCandy();

            // Nangkap
            if (norm(candy - keranjang) < (r_candy + r_keranjang)) {
                score++;
                spawnCandy();
            }

            // Gmbar garisnya seperti rect tapi bulat
            circle(f, candy, r_candy, Scalar(255, 0, 0), -1);
            if (keranjang.x != 0 && keranjang.y != 0) {
                circle(f, keranjang, r_keranjang, Scalar(0, 0, 255), 2);
            }

            // Munculin score
            putText(f, "Score: " + to_string(score), Point(10, 30),
                    FONT_HERSHEY_SIMPLEX, 1, Scalar(0, 255, 0), 2);

            imshow("Permen Catcher", f);

            if (waitKey(30) >= 0) break;
        }
    }
};

int main() {
    Game candyGame;
    candyGame.play();
    return 0;
}
