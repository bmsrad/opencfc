extern "C" void startplcmain();
extern "C" int  task0fun();
extern "C" int startplc()
{
	 startplcmain();
	 return 0;
}
extern "C" int tickt0()
{
	 task0fun();
}

