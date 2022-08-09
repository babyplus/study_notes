@echo off
cd %1
pandoc README.md -o README.docx
cd %~dp0
python docxHandler.py %1