module SomeModule
  use iso_c_binding
  implicit none

  real*8, bind(c), parameter  :: dbl1 = 1.0d0
  real(kind=c_double), bind(c, name="dbl2"), parameter  :: dbl2 = 1.0d0
  integer(kind=c_int), bind(c, name="int1")  :: int1
  type(c_ptr), bind(c, name="ptr1") :: ptr1

contains

  integer function SimpleFunction1() bind(c, name="SimpleFunction1")
    integer :: a
    integer b
    integer :: c

    c = b + a

    SimpleFunction1 = 5

  end function SimpleFunction1


  function SimpleFunction2(val) bind(c, name="SimpleFunction2")
    real*8, intent(in), value  :: val
    real*8                     :: SimpleFunction2
    SimpleFunction2 = 5.0d0
  end function SimpleFunction2


  function SimpleFunction3(val) bind(c, name="SimpleFunction3")
    real*8, intent(in), value  :: val
    type(c_ptr)                :: SimpleFunction3
  end function SimpleFunction3

end module SomeModule

