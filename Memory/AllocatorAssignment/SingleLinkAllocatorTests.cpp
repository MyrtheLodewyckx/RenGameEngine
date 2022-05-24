#include <vld.h>
#include "MemoryOverrides.h"
#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.hpp"
#include "SingleLinkAllocator.h"

using namespace dae;

const size_t allocator_size = 1024;
const size_t pointer_size = sizeof(void*); // this is a different value for x64/Win32 targets

TEST_CASE("Test a single allocation")
{
	SingleLinkAllocator allocator(allocator_size);

	const size_t test_size = allocator_size - pointer_size;
	void* pointer;
	CHECK_NOTHROW(pointer = allocator.Acquire(test_size));
	REQUIRE(pointer != nullptr);
	std::memset(pointer, 1, test_size);
	CHECK_NOTHROW(allocator.Release(pointer));
}

TEST_CASE("Test invalid release")
{
	SingleLinkAllocator allocator(allocator_size);

	void* pointer = new char;
	REQUIRE_THROWS_AS(allocator.Release(pointer), std::runtime_error);
	delete pointer;
}

TEST_CASE("Test two allocations")
{
	SingleLinkAllocator allocator(allocator_size);

	const size_t test_size = allocator_size / 2 - pointer_size;
	void* pointer_a{};
	void* pointer_b{};
	CHECK_NOTHROW(pointer_a = allocator.Acquire(test_size));
	CHECK_NOTHROW(pointer_b = allocator.Acquire(test_size));
	REQUIRE(pointer_a != nullptr);
	REQUIRE(pointer_b != nullptr);
	std::memset(pointer_a, 1, test_size);
	std::memset(pointer_b, 1, test_size);
	CHECK_NOTHROW(allocator.Release(pointer_a));
	CHECK_NOTHROW(allocator.Release(pointer_b));
}

TEST_CASE("Many small allocations")
{
	SingleLinkAllocator allocator(allocator_size);

	const size_t nbPieces = allocator_size / 16;
	void** pointers = new void* [nbPieces];
	const size_t test_size = allocator_size / nbPieces - pointer_size;
	for (int i = 0; i < nbPieces; i++)
	{
		CHECK_NOTHROW(pointers[i] = allocator.Acquire(test_size));
		REQUIRE(pointers[i] != nullptr);
		std::memset(pointers[i], 1, test_size);
	}
	for (int i = 0; i < nbPieces; i++)
		CHECK_NOTHROW(allocator.Release(pointers[i]));
	delete[] pointers;
}


TEST_CASE("Test out of memory")
{
	SingleLinkAllocator allocator(allocator_size);
	const size_t test_size = allocator_size - pointer_size;
	void* pointer;
	CHECK_NOTHROW(pointer = allocator.Acquire(test_size));
	REQUIRE(pointer != nullptr);
	std::memset(pointer, 1, test_size);
	REQUIRE_THROWS_AS(allocator.Acquire(16), std::runtime_error);
	CHECK_NOTHROW(allocator.Release(pointer));
}

class Object
{
public:
	int m_integer{ 0 };
	float m_float{ 0 };
};

TEST_CASE("allocate object 1")
{
	SingleLinkAllocator allocator(4096);

	auto pObject = new(&allocator) Object();

	REQUIRE(pObject->m_integer == 0);
	REQUIRE(pObject->m_float == 0);

	delete pObject;
}