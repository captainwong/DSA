#include "../../include/test/test_list.h"
#include "../../include/dtl/list.h"

using namespace dtl;

int main(int argc, char* arv[])
{
	test::testList<int>(10, WAIT_PAUSE);

	return 0;
}