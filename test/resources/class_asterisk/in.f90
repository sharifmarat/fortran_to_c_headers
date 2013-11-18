module ClassAsteriskMod
  use iso_c_binding
  implicit none

  public :: ClassAsterisk

contains
  subroutine ClassAsterisk(obj1)
    class(*), intent(in)  :: obj1
  end subroutine ClassAsterisk

end module ClassAsteriskMod

