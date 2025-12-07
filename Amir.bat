@echo off
title Commit as Amir Gholami
color 0b

echo.
echo ==================================================
echo      You are now committing as AMIR
echo      Name : Amir Gholami
echo      Email: amir.greav@gmail.com
echo ==================================================
echo.

git config user.name "Amir Grivani"
git config user.email "amir.greav@gmail.com"

echo Git identity switched to Amir Grivani successfully!
echo.
echo Now run these commands (one by one):
echo.
echo    git add .
echo    git commit -m "your descriptive message here"
echo    git push
echo.
echo After push is done, you can close this window.
echo.
pause