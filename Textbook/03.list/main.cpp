#include "../../include/test/test_list.h"

using namespace dtl;

int main(int argc, char* arv[])
{
	test::testList<int>(10, WAIT_NO_WAIT);
	wait(-1);
	return 0;
}
