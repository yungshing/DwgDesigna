(if (not (menugroup "GR"))
(progn
; 加载菜单
(command "menuload" (strcat path "../GR.mns"))
; 显示菜单
(setq i 1 xh t)
(while xh
(if (menucmd (strcat "P" (itoa i) ".1=?"))
(setq i (+ 1 i))
(progn
; 添加菜单到最后
(menucmd (strcat "p" (itoa i) "=+GR.pop1")) (setq i (+ i 1))
)
)
(setq xh nil)
)
)
)
)
)