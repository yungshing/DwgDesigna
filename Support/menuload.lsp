(if (not (menugroup "GR"))
(progn
; ���ز˵�
(command "menuload" (strcat path "../GR.mns"))
; ��ʾ�˵�
(setq i 1 xh t)
(while xh
(if (menucmd (strcat "P" (itoa i) ".1=?"))
(setq i (+ 1 i))
(progn
; ��Ӳ˵������
(menucmd (strcat "p" (itoa i) "=+GR.pop1")) (setq i (+ i 1))
)
)
(setq xh nil)
)
)
)
)
)