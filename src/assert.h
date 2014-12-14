#ifndef ASSERT_H
#define ASSERT_H
#ifdef NDEBUG
	#define assert(x) assert(true)
#else
	#define assert(x) assert(x)
#endif

static void assert(bool condition)
{
	if(condition == false) throw StringException();
}

#endif
