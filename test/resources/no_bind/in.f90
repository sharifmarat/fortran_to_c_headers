module NoBindMod
  use iso_c_binding
  implicit none

  public :: NoBindSub1

contains
  subroutine NoBindSub1(int1, double1, double2, int2) 
    integer(kind=c_int)        :: int1(10)
    real*8, intent(in)         :: double1
    real*8, intent(in), dimension(10, 20, *)              :: double2
    integer             :: int2(:), int5, int6(4)
    intent(in) :: int1, int2
  end subroutine NoBindSub1


  subroutine NoBindSub2
    integer             :: int5, int6(4)
  end subroutine NoBindSub2

  function Func1()
    real*8 :: Func1
    Func1 = 0.0d0
  end function Func1

  real*8 function Func2()
    Func2 = 0.0d0
  end function Func2

  function Func3() result(res)
    real*8  :: res
    res = 0.0d0
  end function Func3

  subroutine WithBind() bind(c)
  end subroutine WithBind

end module NoBindMod

