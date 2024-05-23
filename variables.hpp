const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
const string WINDOW_TITLE = "Cake Tower";

int v[9] = {4, 8, 10, 13, 15, 18, 20, 22, 25};
int velocity = 4; // vận tốc hcn di chuyển qua lại
const int rect_height = 80; // chiều cao mỗi hcn -> cố định
const int init_rect_width = 400; // bề rộng khởi tạo
int latest_width = init_rect_width; // bề rộng hcn gần nhất
int num_of_cakes_in_tower = 0; // giá trị để biết hcn được thả gần nhất là hcn thứ mấy
int score = 0; // điểm của bạn
int difficulty = 1; // ghi nhận độ khó đã chọn
int continue_playing = 1;
bool quit = false;

int perfect_strikes = 0;

void reset_init_value ()
{
    latest_width = init_rect_width;
    num_of_cakes_in_tower = 0;
    score = 0;
    velocity = 4;
    difficulty = 1;
    perfect_strikes = 0;
}

void reset_init_value_when_restarting ()
{
    latest_width = init_rect_width;
    num_of_cakes_in_tower = 0;
    score = 0;
    perfect_strikes = 0;
}

struct High_score
{
    int hs;
    void loadOld()
    {
        ifstream inf ("highscore.txt");
        inf >> hs;
        inf.close();
    }
    void getNew(int score)
    {
        if (score>hs)

        {
            ofstream oef ("highscore.txt", ios::trunc);
            ofstream outf ("highscore.txt");
            outf << score;
            oef.close();
            outf.close();
        }
    }
    void print()
    {
        int score;
        ifstream inf ("highscore.txt");
        inf >> score;
        cout << score;
        inf.close();
    }
    void reset()
    {
        ofstream oef ("highscore.txt", ios::trunc);
        ofstream outf ("highscore.txt");
        outf << "0";
        oef.close();
        outf.close();
    }
};
