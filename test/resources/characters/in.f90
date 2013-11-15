module CharactersMod
  use iso_c_binding
  implicit none

  public :: Characters

contains
  subroutine CharactersNoBind(str1, str2, str3, str4, str5, str6, str7, str8, str9)
    character(len=10, kind=1)   :: str1
    character(10, kind=1)       :: str2
    character(10, 1)            :: str3
    character(kind=1)           :: str4
    character(kind=1, len=10)   :: str5
    character*10                :: str6
    character*(*)               :: str7
    character*(30)              :: str8
    character                   :: str9
  end subroutine CharactersNoBind


  subroutine Characters(str1, str2, str3, str4, str5, str6, str7) bind(c)
    character(len=1, kind=1), value       :: str1
    character(1, kind=1), dimension(50)   :: str2
    character(1, 1), dimension(*)         :: str3
    character(kind=1), dimension(:)       :: str4
    character(kind=1, len=1)              :: str5
    character(len = 1), intent(out)       :: str6
    character, intent(in)                 :: str7

    intent(in)  :: str1, str2
    intent(out) :: str3, str4, str5

  end subroutine Characters

end module CharactersMod

