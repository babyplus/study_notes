cd %1
markdown2confluence README.md |sed s/"language=|"//g > README.confluence 
cd %~dp0
