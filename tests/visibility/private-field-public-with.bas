' TEST_MODE : COMPILE_ONLY_FAIL

type T
	private:
	as integer i
end type

dim as T x
dim as integer n

with x
	n = .i
end with
