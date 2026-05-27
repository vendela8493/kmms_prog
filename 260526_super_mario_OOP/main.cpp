class GameObject
{
public:
    float x, y;
    float width, height;
    
    float vertical_speed, horizontal_speed;
    
    char kind;
    bool is_flying;

    GameObject()
    {
        x = 0;
        y = 0;
        width = 0;
        height = 0;
        vertical_speed = 0;
        horizontal_speed = 0.2;
        kind = ' ';
        is_flying = false;
    }

    void set_object_pos(float obj_pos_x, float obj_pos_y)
    {
        x = obj_pos_x;
        y = obj_pos_y;
    }

    void init_object(float init_x, float init_y, float init_width, float init_height, char init_kind)
    {
        set_object_pos(init_x, init_y);
        width = init_width;
        height = init_height;
        vertical_speed = 0;
        horizontal_speed = 0.2;
        kind = init_kind;
        is_flying = false;
    }
};

int main()
{
    GameObject player;

    player.init_object(39, 10, 3, 3, '@');

    return 0;
}