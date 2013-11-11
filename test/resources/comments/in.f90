module CommentsMod
  use iso_c_binding
  implicit none

  public :: Comments

contains

  ! our sub
  subroutine Comments(int1, double1, int2) bind(c, name="SubroutineWithArgs") ! comments 2
    integer(kind=c_int), value :: int1      !< int 1 !!!
    real*8, intent(in)         :: double1   !< int 2 !!!
    integer, value             :: int2      !< int 3

    ! attributes
    intent(in) :: int1, int2        !< attributes
    value double1                   !< attributes

  end subroutine Comments

  ! subroutine 2
  ! subroutine Comments(int1, double1, int2) bind(c, name="SubroutineWithArgs") ! comments 2
  !   integer(kind=c_int), value :: int1      !< int 1 !!!
  !   real*8, intent(in)         :: double1   !< int 2 !!!
  !   integer, value             :: int2      !< int 3

  !   ! attributes
  !   intent(in) :: int1, int2        !< attributes
  !   value double1                   !< attributes

  ! end subroutine Comments

end module Comments

