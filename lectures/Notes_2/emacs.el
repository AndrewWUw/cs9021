; Emacs customisation file
; Written by Eric Martin for COMP9021

(custom-set-variables
'(default-frame-alist (quote ((menu-bar-lines . 1) (foreground-color . "Black") (background-color . "Ivory1") (cursor-color . "Red") (vertical-scroll-bars . right) (tool-bar-lines . 1) (height . 43) (width . 100) (top . 0) (left . 25) (fringe) (left-fringe) (right-fringe . 0))))
 '(gdb-show-main t)
 '(indicate-empty-lines t)
 '(initial-frame-alist (quote ((top . 0) (left . 25) (height . 52) (width . 130))))
 '(mouse-autoselect-window t)
 '(text-mode-hook (quote (text-mode-hook-identify)))
 '(tooltip-hide-delay 1000)
 '(transient-mark-mode t)
 '(visible-bell t))

(global-set-key "\C-co" 'c-open-and-prepare)
(global-set-key "\C-cp" 'c-prepare)

(add-hook 'c-mode-common-hook
	  '(lambda ()
	     ;; use spaces instead of tabs
	     (setq indent-tabs-mode nil)
	     (c-toggle-auto-hungry-state)
	     (define-key c-mode-map "\C-m" 'c-context-line-break)
	     (c-add-style "PERSONAL"
			  '(
			    ;; do not automatically insert a new line
			    ;; after a semi-colon if the next line
			    ;; is not empty
			    (c-hanging-semi&comma-criteria
			     c-semi&comma-no-newlines-before-nonblanks
			     c-semi&comma-inside-parenlist)
			    (c-hanging-braces-alist
			     ;; for array initializations
			     (brace-list-open)
			     (brace-list-close)
			     (brace-list-intro)
			     (brace-entry-open)
			     ;; for function definitions
			     (defun-open after)
			     ;; for beginning of block constructs
			     (substatement-open after)
			     ;; for end of block constructs
			     (block-close . c-snug-do-while)
			     ;; for beginning of struct constructs
			     (class-open after)
			     ;; for end of struct constructs
			     (class-close))
			    (c-hanging-colons-alist
			     ;; for switch constructs
			     (case-label after))
			    (c-offsets-alist
			     ;; for strings displayed across many lines
			     (string 0)
			     ;; for switch constructs
			     (case-label 4)))
			  t)))

(defun c-prepare ()
  "Facilitates the compilation and debugging of C programs.
In a frame that displays a .c file,
and possibly the *compilation* or *gud-a.out* buffer,
- creates an associated Makefile with the _getfilenames and _mmakefile perl scripts,
unless a Makefile not created by _mmakefile already exists;
- runs make;
- if the compilation is successful, launches gdb,
replaces the *compilation* buffer by the *gud-a.out* buffer,
and leaves point in *gud-a.out* buffer;
- if the compilation is not successful, places point on line of first error
in the buffer that displays the source file.
The point can be either in the window that displays the .c file,
or in the window that displays the *compilation* or *gud-a.out* buffers,
and the .c file will be silently saved.
The .c file F that is displayed might contain pathnames to other source files (that can contain
spaces, can leave out the .c extension, can be relative or absolute but should not start in ~,
and can be preceded or followed by spaces or stars) between a line that contains an
occurrence of 'Other .c source files, if any, one per line, starting on the next line:'
and a line all of whose nonblank characters are stars with a closing comment */ after all
stars, possibly with lines containing nothing but spaces or stars in-between.
Exactly one of F and the other files must contain a main() function, and
the Makefile will be generated in the directory where that file resides."
  (interactive)
  (if (string-match "\*\\(compilation\\|gud-a.out\\)\*"
		    (buffer-name (current-buffer)))
      (other-window 1))
  (save-buffer)
  (let* ((file (buffer-file-name))
	 (getfilenames-proc (start-process "getfilenames-process" nil "_getfilenames" file)))
    (set-process-filter getfilenames-proc 'c-getfilenames)
    (while (eq (process-status getfilenames-proc) 'run)
      (sleep-for 1))
    (if (not (= (process-exit-status getfilenames-proc) 0))
	(progn
	  (message files)
	  (message "No Makefile can be generated from the provided set of files"))
      (c-create-makefile files)
      ;; _getfilenames returns:
      ;; - the absolute directory where the source file with the main() function resides,
      ;; - the absolute pathname to the source file with the main() function, and
      ;; - the absolute pathnames to all source files, including the latter and
      ;; lexicographically ordered.
      ;; Space separate these pathnames, and spaces in pathnames have been replaced
      ;; by Control B characters.
      ;; These control B characters are replaced by unescaped spaces in the first two pathnames
      ;; returned by _getfilenames, in accordance with their original values,
      ;; so that they can be processed properly by Lisp Emacs.
      (let* ((main-dir (replace-regexp-in-string "" " " (car (split-string files))))
	     (main-file (replace-regexp-in-string "" " " (cadr (split-string files))))
	     (all-files (cddr (split-string files))))	   
	(if (file-exists-p (concat main-dir "Makefile"))
	    (c-compile-and-run-debugger main-dir main-file all-files)
	  (message "No Makefile can be generated from the provided set of files")
	  (delete-other-windows))))))

(defun c-open-and-prepare (file)
  "Opens or creates a .c file and prepares compilation, debugging and running.
- Takes a file name as single argument, with either no extension
or with the .c extension.
- If such a file does exist, uses it; otherwise, creates one with the _mctemplate shell script,
prompting the user to reply yes or no to the question whether he or she wants a template
for a one file program rather than for a multifile program. If the answer is no then the template
will include the line 'Other .c source files, if any, one per line, starting on the next line:'
needed for programs that span many files. Answering yes produces a template for a sourcefile meant
to contain the full program.
- Opens the file in a new buffer.
- Creates an associated Makefile with the _mmakefile perl script,
unless a Makefile not created by _mmakefile already exists.
- If the file has been created by _mctemplate, places the point to insert
a short description after 'Description: '.
- If the file has not been created by _mctemplate, runs make.
- If the compilation is successful, launches gdb,
replaces the *compilation* buffer by the *gud-a.out* buffer,
and leaves point in *gud-a.out* buffer.
- If the compilation is not successful, places point on line of first error
in the buffer that displays the source file.
The .c file F that is displayed might contain pathnames to other source files (that can contain
spaces, can leave out the .c extension, can be relative or absolute but should not start in ~,
and can be preceded or followed by spaces or stars) between a line that contains an
occurrence of 'Other .c source files, if any, one per line, starting on the next line:'
and a line all of whose nonblank characters are stars with a closing comment */ after all
stars, possibly with lines containing nothing but spaces or stars in-between.
Exactly one of F and the other files must contain a main() function, and
the Makefile will be generated in the directory where that file resides."
  (interactive "FEnter name of main file for a C program: ")
  ;; expand-file-name converts a possibly relative pathname to a full pathname,
  ;; and deals properly with ~ or ~username.
  (setq file (expand-file-name (concat (file-name-sans-extension file) ".c")))
  (delete-other-windows)
  (if (not (file-exists-p file))
      (c-open-new-file file)
    (find-file file)
    (let* ((file (buffer-file-name))
	   (getfilenames-proc (start-process "getfilenames-process" nil "_getfilenames" file)))
      (set-process-filter getfilenames-proc 'c-getfilenames)
      (while (eq (process-status getfilenames-proc) 'run)
	(sleep-for 1))
      (if (not (= (process-exit-status getfilenames-proc) 0))
	  (progn
	    (message files)
	    (message "No Makefile can be generated from the provided set of files"))
	(c-create-makefile files)
	;; _getfilenames returns:
	;; - the absolute directory where the source file with the main() function resides,
	;; - the absolute pathname to the source file with the main() function, and
	;; - the absolute pathnames to all source files, including the latter and
	;; lexicographically ordered.
	;; Space separate these pathnames, and spaces in pathnames have been replaced
	;; by Control B characters.
	;; These control B characters are replaced by unescaped spaces in the first two pathnames
	;; returned by _getfilenames, in accordance with their original values,
	;; so that they can be processed properly by Lisp Emacs.
	(let* ((main-dir (replace-regexp-in-string "" " " (car (split-string files))))
	       (main-file (replace-regexp-in-string "" " " (cadr (split-string files))))
	       (all-files (cddr (split-string files))))	   
	  (if (file-exists-p (concat main-dir "Makefile"))
	      (c-compile-and-run-debugger main-dir main-file all-files)
	    (message "No Makefile can be generated from the provided set of files")
	    (delete-other-windows)))))))

(defun c-open-new-file(file)
  (if (yes-or-no-p "Do you want a template for a one file rather than a multifile program? ")
      (call-process "_mctemplate" nil nil nil file "t")
    (call-process "_mctemplate" nil nil nil file ""))
  (find-file file)
  (beginning-of-buffer)
  (search-forward "Description: "))

(defun c-getfilenames (process output)
  (setq files output))

(defun c-create-makefile (files)
  ;; Lips emacs is happy with spaces in pathnames, as long as they are not escaped.
  (let ((makefile (concat (replace-regexp-in-string "" " " (car (split-string files))) "Makefile")))
    (if (file-exists-p makefile)
	;; Has this Makefile been created by mmakefile?
	(if (not (zerop (call-process "grep" nil nil nil "-qs"
				      "^# Makefile produced by _mmakefile$"
				      makefile)))
	    ;; No, so we keep this Makefile, whether it is for this source file or not.
	    (message "A Makefile not produced by _mmakefile exists.
I have not replaced it.")
	  ;; Yes, we will replace it.
	  (call-process "rm" nil nil nil makefile)))
    ;; If a Makefile needs to be created, we create it.
    (if (not (file-exists-p makefile))
	(call-process-shell-command "_mmakefile" nil nil nil files))))

(defun c-compile-and-run-debugger (main-dir main-file all-files)
  (let ((makefile (concat main-dir "Makefile"))
	(a-out (concat main-dir "a.out")))
    (if (not (zerop (call-process "grep" nil nil nil "-Eqs"
				  "^# Makefile produced by _mmakefile$"
				  makefile)))
	(message "Makefile no produced by _mmakefile; hope that's what you want..."))	   
    (if (file-exists-p a-out)
	(delete-file a-out))
    (compile (concat "make -C \"" main-dir "\""))
    (while (eq (process-status "compilation") 'run)
      (sleep-for 1))
    (if (file-exists-p a-out)
	;; The compilation was successful.
	;; We start or restart gud if this is the first file being compiled,
	;; or if we are compiling files for a new a.out file, or if we quit the debugger,
	;; or if we (maybe inadvertently) got rid of the *gud-a.out* buffer.
	(if (or	(not (boundp 'c-last-main-dir))
		(not (equal c-last-main-dir main-dir))
		(not (equal c-last-files all-files))
		(and (eq (get-process "gud-a.out") nil)
		     (eq (get-process "gud-a.out<1>") nil)))
	    (progn
	      (setq c-last-main-dir main-dir)
	      (setq c-last-files all-files)
	      (if (get-buffer "\*gud-a.out\*")
		  (kill-buffer (get-buffer "\*gud-a.out\*")))
              (delete-other-windows)
	      (find-file main-file)
	      (gdb "gdb -q --annotate=3 a.out")
	      (gud-tooltip-mode t)
	      (split-window-vertically)
	      (switch-to-buffer (get-buffer main-file))
	      (enlarge-window (/ (window-height) 2))
	      (other-window 1))
	  ;; We are compiling source files for the same a.out file, and switch
	  ;; from the *compilation* window to the *gud-a.out* window.
	  (enlarge-window (/ (window-height) 2))
	  (other-window 1)
	  (switch-to-buffer (get-buffer "\*gud-a.out\*"))
	  (end-of-buffer))
      ;; The compilation was unsuccessful.
      ;; We go to the first error in the buffer that displays the source code.
      (next-error))))



