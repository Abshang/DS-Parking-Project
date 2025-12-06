@echo off
title Commit as Fatemeh Abshang
color 0a

echo.
echo ==================================================
echo      You are now committing as FATEMEH
echo      Name : Fatemeh Abshang
echo      Email: abshangfatemeh3717@gmail.com
echo ==================================================
echo.

git config user.name "Fatemeh Abshang"
git config user.email "abshangfatemeh3717@gmail.com"

echo Git identity switched to Fatemeh Abshang successfully!
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