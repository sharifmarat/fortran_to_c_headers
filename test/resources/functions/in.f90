module SimpleFunctionMod
  use iso_c_binding
  implicit none

contains

  integer function SimpleFunction() bind(c, name="SimpleFunction")
    integer :: a
    integer b
    integer :: c

    c = b + a

    SimpleFunction = 5

  end function SimpleFunction

end module SimpleFunctionMod
