;; .emacs

;; Add a local directory to the load-path
(setq load-path
      (append load-path
              '("/home/jeremy/mylisp/")))

;; Kill the toolbar
(tool-bar-mode -1)

;; Some lovely tool stuff
(require 'cppgen)
(require 'php-mode)

;; start emacs in server mode
;;(server-start)

;; Set initial frame size
(setq initial-frame-alist
      `((left . 0) (top . 0)
        (width . 120) (height . 40)))

;;; uncomment this line to disable loading of "default.el" at startup
;;(setq inhibit-default-init t)

;; enable visual feedback on selections
(setq transient-mark-mode t)

;; default to better frame titles
(setq frame-title-format
      (concat  "%b - emacs@" (system-name)))

;; default to unified diffs
(setq diff-switches "-u")

;; always end a file with a newline
;;(setq require-final-newline 'query)

;;; uncomment for CJK utf-8 support for non-Asian users
;; (require 'un-define)
(custom-set-variables
 ;; custom-set-variables was added by Custom.
 ;; If you edit it by hand, you could mess it up, so be careful.
 ;; Your init file should contain only one such instance.
 ;; If there is more than one, they won't work right.
 '(delete-selection-mode t)
 '(inhibit-startup-screen t)
 '(mouse-drag-copy-region t)
 '(pov-run-default "%s")
 '(povray-command "jezz_render")
 '(scroll-bar-mode (quote right))
 '(speedbar-default-position (quote right))
 '(speedbar-query-confirmation-method (quote none-but-delete))
 '(speedbar-show-unknown-files t)
 '(tooltip-mode nil))
(custom-set-faces
 ;; custom-set-faces was added by Custom.
 ;; If you edit it by hand, you could mess it up, so be careful.
 ;; Your init file should contain only one such instance.
 ;; If there is more than one, they won't work right.
 )

;; Fonts
;; ============
;;
(setq font-lock-maximum-decoration t)
(add-hook 'emacs-lisp-mode-hook 'turn-on-font-lock)
(add-hook 'cc-mode-hook 'turn-on-font-lock)
(add-hook 'c-mode-hook 'turn-on-font-lock)
(add-hook 'c++-mode-hook 'turn-on-font-lock)
(add-hook 'java-mode-hook 'turn-on-font-lock)
(add-hook 'sh-mode-hook 'turn-on-font-lock)
(add-hook 'shell-script-mode-hook 'turn-on-font-lock)
(add-hook 'makefile-mode-hook 'turn-on-font-lock)
(add-hook 'perl-mode-hook 'turn-on-font-lock)
(add-hook 'xrdb-mode-hook 'turn-on-font-lock)
(add-hook 'ps-mode-hook '(lambda ()
                           (make-local-variable 'font-lock-support-mode)
                           (make-local-variable 'lazy-lock-defer-on-scrolling)
                           (setq font-lock-support-mode 'lazy-lock-mode
                                 lazy-lock-defer-on-scrolling t)
                           (turn-on-font-lock)))
(add-hook 'ps-run-mode-hook '(lambda () (turn-on-font-lock)))


;; Window colors
;; =============
;;
(if (eq window-system 'x)
    (if (x-display-color-p)
        (progn
          (set-background-color "black")
          (set-foreground-color "yellow")
          (set-face-background 'region "yellow")
          (set-face-foreground 'region "black")
          (set-face-background 'highlight "green")
          (set-face-foreground 'highlight "red")
          ;;(set-face-background 'modeline "green")
          ;;(set-face-foreground 'modeline "black")
          (setq x-pointer-shape x-pointer-left-ptr)
          (set-cursor-color "red")
          (set-mouse-color "blue")
          )))

;; Mode Options
;; ============
(autoload 'processing-mode "processing-mode" "Processing mode" t)
(autoload 'php-mode "php-mode" "Major mode for editing php code." t)
(autoload 'c++-mode  "cc-mode" "C++ Editing Mode" t)
(autoload 'c-mode    "cc-mode" "C Editing Mode"   t)
(autoload 'objc-mode "cc-mode" "Objective C Editing Mode" t)
(autoload 'text-mode "indented-text-mode" "Indented Text Editing Mode" t)
(autoload 'xrdb-mode "xrdb-mode" "Mode for editing X resource files" t)
(autoload 'ps-mode "ps-mode" "Major mode for editing PostScript" t)
(setq auto-mode-alist
      (append '(("\\.C$"       . c++-mode)
                ("\\.cc$"      . c++-mode)
                ("\\.cpp$"     . c++-mode)
                ("\\.c$"       . c-mode)
                ("\\.h$"       . c++-mode)
                ("\\.hpp$"     . c++-mode)
                ("\\.i$"       . c++-mode)
                ("\\.ii$"      . c++-mode)
                ("\\.m$"       . objc-mode)
                ("\\.pl$"      . perl-mode)
                ("\\.sql$"     . c-mode)
                ("\\.sh$"      . shell-script-mode)
                ("\\.mak$"     . makefile-mode)
                ("\\.GNU$"     . makefile-mode)
                ("makefile$"   . makefile-mode)
                ("Imakefile$"  . makefile-mode)
                ("\\.Xdefaults$"    . xrdb-mode)
                ("\\.Xenvironment$" . xrdb-mode)
                ("\\.Xresources$"   . xrdb-mode)
                ("*.\\.ad$"         . xrdb-mode)
                ("\\.[eE]?[pP][sS]$" . ps-mode)
                ("\\.php$" . php-mode)
                ("\\.inc$" . php-mode)
                ("\\.pde$" . processing-mode)
                ) auto-mode-alist))

;; C++ Style
;; =========
;;

(defconst my-c-style
  '(
    (c-echo-syntactic-information-p . t)
    (c-basic-offset                 . 2)
    (c-toggle-auto-state            . t)
    (c-offsets-alist .
                     ((string                . +)
                      (c                     . +)
                      (defun-open            . 0)
                      (defun-close           . 0)
                      (defun-block-intro     . +)
                      (class-open            . 0)
                      (class-close           . 0)
                      (inline-open           . 0)
                      (inline-close          . 0)
                      (extern-lang-open      . 0)
                      (extern-lang-close     . 0)
                      (func-decl-cont        . +)
                      (knr-argdecl-intro     . +)
                      (knr-argdecl           . +)
                      (topmost-intro         . 0)
                      (topmost-intro-cont    . +)
                      (member-init-intro     . +)
                      (member-init-cont      . +)
                      (inher-intro           . +)
                      (inher-cont            . +)
                      (block-open            . 0)
                      (block-close           . 0)
                      (brace-list-open       . 0)
                      (brace-list-close      . 0)
                      (brace-list-intro      . +)
                      (brace-list-entry      . 0)
                      (statement             . 0)
                      (statement-cont        . +)
                      (statement-block-intro . +)
                      (statement-case-intro  . +)
                      (statement-case-open   . 0)
                      (substatement          . +)
                      (substatement-open     . 0)
                      (case-label            . +)
                      (access-label          . -)
                      (label                 . 0)
                      (do-while-closure      . 0)
                      (else-clause           . 0)
                      (catch-clause          . 0)
                      (comment-intro         . 0)
                      (arglist-intro         . c-lineup-arglist-intro-after-paren)
                      (arglist-cont          . c-lineup-arglist)
                                        ;              (arglist-cont-nonempty . +)
                      (arglist-cont-nonempty . c-lineup-arglist-intro-after-paren)
                      (arglist-close         . c-lineup-arglist)
                      (stream-op             . +)
                      (inclass               . +)
                      (inextern-lang         . +)
                      (cpp-macro             . 0)
                      (friend                . 0)
                      (objc-method-intro     . +)
                      (objc-method-args-cont . +)
                      (objc-method-call-cont . +)
                      ))

    (c-comment-only-line-offset . (0 . -1000))
    (c-hanging-braces-alist     . ((substatement-open after)
                                   (brace-list-open)))
    (c-hanging-colons-alist     . ((member-init-intro before)
                                   (inher-intro)
                                   (case-label after)
                                   (label after)
                                   (access-label after)))
    (c-cleanup-list             . ((scope-operator
                                    empty-defun-braces
                                    defun-close-semi)))

    )
  "Pavier C++ Programming Style")


(defun my-c-mode-common-hook ()
  (c-add-style "pavier" my-c-style t)
  (c-toggle-auto-hungry-state t)
  ;;(cpp-build-menu)
  ;;
  ;; Key Bindings
  ;;
  ;; (if cpp-mode-map
  ;;     nil
  ;;   (setq cpp-mode-map (make-keymap))
  ;;   (define-key cpp-mode-map "\C-c x"
  ;;     'cpp-context)
  ;;   (define-key cpp-mode-map "\C-c c"
  ;;     'cpp-class)
  ;;   )
  )

(add-hook 'c-mode-common-hook 'my-c-mode-common-hook)

;; To use abbrev-mode, add lines like this:
(add-hook 'php-mode-hook
          '(lambda () (define-abbrev php-mode-abbrev-table "ex" "extends")))

(global-set-key [f1] 'iwbs)
(global-set-key [f12] 'open-dot-emacs)


;; Start speedbar
(speedbar-frame-mode)
;;(split-window-horizontally)


;; http://emacsblog.org/2007/01/17/indent-whole-buffer/
(defun iwb ()
  "indent whole buffer"
  (interactive)
  (delete-trailing-whitespace)
  (indent-region (point-min) (point-max) nil)
  (untabify (point-min) (point-max)))

(defun iwbs ()
  "indent whole buffer and save"
  (interactive)
  (delete-trailing-whitespace)
  (indent-region (point-min) (point-max) nil)
  (untabify (point-min) (point-max))
  (save-buffer))

(defun open-dot-emacs ()
  "opening-dot-emacs"
  (interactive) ;this makes the function a command too
  (find-file "~/.emacs")
  )
