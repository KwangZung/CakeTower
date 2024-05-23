bool if_clicked (int mouse_x, int mouse_y, int pos_w, int pos_h, int pos_x, int pos_y)
{
    return ((mouse_x >= pos_x && mouse_x <= pos_x+pos_w) && (mouse_y >= pos_y && mouse_y <= pos_y+pos_h));
}


