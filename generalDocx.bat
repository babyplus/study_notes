@echo off
cd %1
pandoc README.md -o README.docx
cd ..
python docxHandler.py %1