' TEST_MODE : COMPILE_ONLY_FAIL

type Parent
	as integer i
	declare constructor( byval as integer )
end type

constructor Parent( byval i as integer )
	this.i = i
end constructor

type Child extends Parent
	declare constructor( )
	declare constructor( byref as Child )
end type

constructor Child( )
	base( )
end constructor

constructor Child( byref rhs as Child )
	base( 123 )
end constructor

dim as Child x
