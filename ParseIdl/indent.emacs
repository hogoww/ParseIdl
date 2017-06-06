#!/usr/bin/emacs --script

(setq require-final-newline 'visit)

(defun indent-files (file)
  (if (not (eq "" file))
      (progn
       (find-file file)
       (indent-region (point-min) (point-max))
       (save-buffer)
       (kill-buffer))
    (princ "you didn't give any file to treat\n")))

(indent-files (car command-line-args-left))


