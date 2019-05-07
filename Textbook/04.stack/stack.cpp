#include "../../include/test/test_stack.h"
#include "test_convert.h"


int main(int argc, char* argv[])
{
	chapter_4_3_1::test_convert();
	dtl::test::testStack<int>(10);
}
