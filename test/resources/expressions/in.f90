module ExpressionsMod
  use iso_c_binding
  implicit none

  integer, parameter  :: PARAM = 10
  integer, parameter  :: KR = 8

contains

  pure integer function GetLength(a, b, str)
    integer, intent(in) :: a
    integer, intent(in) :: b
    character(len=*), intent(in)  :: str

    GetLength = 5

  end function GetLength


  pure function GetOffset(val1, val2) bind(c, name="GetOffset")
    real*8, intent(in), value  :: val1
    real*8, intent(in), value  :: val2
    integer                    :: GetOffset
    real*8 a
    a = 0
    a = 0.
    a = 0.0
    a = 0d0
    a = 0.d0
    a = 0.e+3_KR
    a = 0_KR
    GetOffset = 5
  end function GetOffset


  subroutine Expressions(val, str) bind(c, name="Expressions")
    real*8, intent(in), value  :: val
    character(kind=c_char, len=1), dimension(GetLength(1, 2+3, "blah") - GetOffset(3.0E+3_KR, -3.86D-67) + 3 - 1 + PARAM)  :: str
    intent(in) :: str
    character(len=GetLength(1, 2+3, "blah") - GetOffset(3.0E+3_KR, -3.86D-67) + 3 - 1 + PARAM) :: tmp_str
  end subroutine Expressions

end module ExpressionsMod
