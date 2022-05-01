; nbrhdnash.nsi
;--------------------------------

; The name of the installer
Name "nbrhdnash"

; The file to write
OutFile "nbrhdnash.exe"

; Request application privileges for Windows Vista and higher
RequestExecutionLevel admin

; Build Unicode installer
Unicode True

; The default installation directory
InstallDir $APPDATA\nbrhdnash

; Registry key to check for directory (so if you install again, it will
; overwrite the old one automatically)
InstallDirRegKey HKLM "Software\nbrhdnash" "Install_Dir"

;--------------------------------

; Pages

Page components
Page directory
Page instfiles

UninstPage uninstConfirm
UninstPage instfiles

;--------------------------------

; The stuff to install
Section "NeighbourhoodNash (required)"

  SectionIn RO

  ; Set output path to the installation directory.
  SetOutPath $INSTDIR

  ; Put file there
  File /r "L:\3GE_GroupD_Build\bin\Release\*"

  ; Write the installation path into the registry
  WriteRegStr HKLM SOFTWARE\nbrhdnash "Install_Dir" "$INSTDIR"

  ; Write the uninstall keys for Windows
  WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\nbrhdnash" "DisplayName" "NeighbourhoodNash"
  WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\nbrhdnash" "UninstallString" '"$INSTDIR\uninstall_nbrhdnash.exe"'
  WriteRegDWORD HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\nbrhdnash" "NoModify" 1
  WriteRegDWORD HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\nbrhdnash" "NoRepair" 1
  WriteUninstaller "$INSTDIR\uninstall_nbrhdnash.exe"

SectionEnd

; Optional section (can be disabled by the user)
Section "Start Menu Shortcuts"

  CreateDirectory "$SMPROGRAMS\nbrhdnash"
  CreateShortcut "$SMPROGRAMS\nbrhdnash\Uninstall.lnk" "$INSTDIR\uninstall_nbrhdnash.exe"
  CreateShortcut "$SMPROGRAMS\nbrhdnash\nbrhdnash (MakeNSISW).lnk" "$INSTDIR\nbrhdnash.nsi"
  CreateShortcut "$desktop\NeighbourhoodNash.lnk" "$instdir\nbrhdnash.exe"

SectionEnd

Section "Desktop Shortcut"

  CreateShortcut "$desktop\NeighbourhoodNash.lnk" "$instdir\nbrhdnash.exe"

SectionEnd


;--------------------------------

; Uninstaller

Section "Uninstall"

  ; Remove registry keys
  DeleteRegKey HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\nbrhdnash"
  DeleteRegKey HKLM SOFTWARE\nbrhdnash

  ; Remove files and uninstaller
  RMDir /r $INSTDIR

  ; Remove shortcuts, if any
  Delete "$SMPROGRAMS\nbrhdnash\NeighbourhoodNash.lnk"
  Delete "$desktop\NeighbourhoodNash.lnk"

  ; Remove directories
  RMDir "$SMPROGRAMS\nbrhdnash"
  RMDir "$INSTDIR"

SectionEnd
