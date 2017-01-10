class server
{
public:
    server() 
    {
        getsocket();
        tp.init()
    }
    void startAccept();
    void stop()
    {
        closesocket();
        tp.destroy();
    }
private:
    getsocket();
    threadpool tp  
};
