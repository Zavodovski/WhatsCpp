struct node
{
    int x, y;
    bool operator< (const node& b) const
    {
        //return this->x < b.x;  //大顶堆
        return this->x > b.x;  //小顶堆
    }
};