(defvar cpp-mode-map nil
  "Keymap for this package")

(defvar cpp-left-window nil
  "Placeholder for left window")

(defvar cpp-right-window nil
  "Placeholder for right window")

(defvar cpp-global-classname
  "Class name for C++ Code Generator in current context.")

(defvar cpp-global-testclassname
  "Test class name for C++ Code Generator in current context.")

(defvar cpp-global-namespace (getenv "CPP_NAMESPACE")
  "Namespace for C++ Code Generator in current context. Set in env variable CPP_NAMESPACE.")

(defvar cpp-global-uclassname
  "Upper case class name for C++ Code Generator in current context.")

(defvar cpp-global-hdr-name)
(defvar cpp-global-impl-name)
(defvar cpp-global-testhdr-name)
(defvar cpp-global-hdr-postfix ".H")
(defvar cpp-global-impl-postfix ".C")
(defvar cpp-global-timestamp-format "%Y%m%d%H%M%S")

(defun cpp-iwbs ()
  "Indent whole buffer and save"
  (delete-trailing-whitespace)
  (indent-region (point-min) (point-max) nil)
  (untabify (point-min) (point-max))
  (save-buffer))

;;
;; Boilerplate
;;
(defun cpp-open-include-guard ()
  "Create opening include guards in the current buffer"
  (insert (concat "#ifndef " cpp-global-uclassname "_H\n"))
  (insert (concat "#define " cpp-global-uclassname "_H\n\n"))
  )

(defun cpp-close-include-guard ()
  "Create closing include guards in the current buffer"
  (insert (concat "#endif // " cpp-global-uclassname "_H\n"))
  )

(defun cpp-open-namespace ()
  "Create opening namespace tag in the current buffer"
  (insert (concat "namespace " cpp-global-namespace "\n{ // NSP_BEG_TAG " cpp-global-namespace "\n"))
  )

(defun cpp-close-namespace ()
  "Create closing namespace tag in the current buffer"
  (insert (concat "} // NSP_END_TAG " cpp-global-namespace "\n"))
  )

(defun cpp-using-namespace ()
  "Using namespace string"
  (insert "using namespace " cpp-global-namespace ";\n\n")
  )

;;
;; Class Header File
;;
(defun cpp-hdr-decl ()
  "Create class header declaration"
  (insert (concat "class " cpp-global-classname "\n{ // DECL_BEG_TAG " cpp-global-classname "\n"))
  (insert "public: // METHODS\n\nprotected: // METHODS\n\nprivate: // METHODS\n\n")
  (insert "public: // MEMBERS\n\nprotected: // MEMBERS\n\nprivate: // MEMBERS\n\n")
  (insert (concat "}; // DECL_END_TAG " cpp-global-classname "\n"))
  )

(defun cpp-hdr ()
  "Create the header for the new C++ class"
  (find-file cpp-global-hdr-name)
  (cpp-open-include-guard)
  (cpp-open-namespace)
  (cpp-hdr-decl)
  (cpp-close-namespace)
  (cpp-close-include-guard)
  (cpp-iwbs)
  )

;;
;; Class Implementation File
;;
(defun cpp-impl ()
  "Create the implementation for the new C++ class"
  (find-file cpp-global-impl-name)
  (cpp-protected-include cpp-global-classname)
  (cpp-open-namespace)
  ;; some more code here
  (cpp-close-namespace)
  (cpp-iwbs)
  )

(defun cpp-new-method (type name params)
  "Create the implementation for the new C++ class method"
  (find-file cpp-global-impl-name)
  (goto-char (point-min))
  (search-forward "NSP_END_TAG")
  (forward-line -1)
  (forward-line 1)
  (insert (concat " // METH_BEG_TAG " cpp-global-namespace "_" (downcase cpp-global-classname) "_" (downcase type) "_" (downcase name) "_" ))
  (insert (format-time-string cpp-global-timestamp-format (current-time)))
  (insert ".C\n")
  (insert (concat type " " cpp-global-classname "::" name " (" params ")\n{\n"))
  (insert (concat " // Implement here\n}\n // METH_END_TAG\n\n"))
  (sleep-for 0.1)
  (cpp-iwbs)
  )

;;
;; Class Test Header File
;;
(defun cpp-testhdr-decl ()
  "Create class header declaration"
  (insert (concat "class " cpp-global-testclassname " : public CxxTest::TestSuite\n{ // DECL_BEG_TAG " cpp-global-classname "\n"))
  (insert "public: // CASES\n\nvoid testSuite(void)\n{\nTS_ASSERT(true);\n}\n\n")
  (insert "public: // FIXTURES\n\nvoid setUp()\n{\n  // Implement here\n}\n\nvoid tearDown()\n{\n  // Implement here\n}\n\nprivate:\n\n")
  (insert (concat "\n}; // DECL_END_TAG " cpp-global-testclassname "\n"))
  )

(defun cpp-test-hdr ()
  "Create the header for the new C++ class"
  (find-file cpp-global-testhdr-name)
  (insert "#include <cxxtest/TestSuite.h>\n\n")
  (cpp-protected-include cpp-global-classname)
  (cpp-using-namespace)
  (cpp-testhdr-decl)
  (cpp-iwbs)
  )

;;
;; Commands
;;

(defun cpp-protected-include (class)
  "Create a protected inclusion for the class header"
  (interactive "sClass: ")
  (insert (concat "#ifndef " (upcase class) "_H\n"))
  (insert (concat "#include <" (capitalize class) ".H>\n"))
  (insert "#endif\n\n")
  )

(defun cpp-protected-hdr-inclusion (class)
  "Create a protected inclusion for the class header"
  (interactive "sClass: ")
  (find-file cpp-global-hdr-name)
  (goto-char (point-min))
  (search-forward "NSP_BEG_TAG")
  (forward-line -1)
  (cpp-protected-include class)
  (cpp-iwbs)
  )

(defun cpp-protected-impl-inclusion (class)
  "Create a protected inclusion for the class implementation"
  (interactive "sClass: ")
  (find-file cpp-global-impl-name)
  (goto-char (point-min))
  (search-forward "NSP_BEG_TAG")
  (forward-line -1)
  (cpp-protected-include class)
  (cpp-iwbs)
  )

(defun cpp-new-test-case (name)
  "Create a new test case"
  (interactive "sName: ")
  (find-file cpp-global-testhdr-name)
  (goto-char (point-min))
  (search-forward "public: // CASES")
  (forward-line 1)
  (setq local-ctr (% (car (cdr (current-time))) 1000000))
  (setq local-ctr-str (format "%06d" local-ctr))
  (insert (concat "\nvoid test_" local-ctr-str "_" name "(void)\n{\n"))
  (insert (concat "TS_WARN(\"TO DO: Write test" name " for " cpp-global-classname ".\");\n"))
  (insert (concat "TS_FAIL(\"test" name " not yet implemented.\");\n}\n"))
  (sleep-for 0.5)
  (cpp-iwbs)
  )

(defun cpp-new-structors (name)
  "Create a new public method"
  (interactive "sName: ")
  (find-file cpp-global-hdr-name)
  (goto-char (point-min))
  (search-forward "public: // METHODS")
  (forward-line 1)
  (insert (concat name " ();\n"))
  (insert (concat "~" name " ();\n"))
  (goto-char (point-min))
  (search-forward "private: // METHODS")
  (forward-line 1)
  (insert (concat name " (const " name "&);\n"))
  (insert (concat name "& operator = (const " name "&);\n"))
  (cpp-iwbs)
  (cpp-new-method "" name "")
  (cpp-new-method "" (concat "~" name) "")
  ;;(cpp-new-test-case name)
  )

(defun cpp-new-pub-method (type name params)
  "Create a new public method"
  (interactive "sType: \nsName: \nsParameters")
  (find-file cpp-global-hdr-name)
  (goto-char (point-min))
  (search-forward "public: // METHODS")
  (forward-line 1)
  (insert (concat " " type " " name " (" params ");\n"))
  (cpp-iwbs)
  (cpp-new-method type name params)
  (cpp-new-test-case name)
  )

(defun cpp-new-pri-method (type name params)
  "Create a new private method"
  (interactive "sType: \nsName: \nsParameters")
  (find-file cpp-global-hdr-name)
  (goto-char (point-min))
  (search-forward "private: // METHODS")
  (forward-line 1)
  (insert (concat " " type " " name " (" params ");\n"))
  (cpp-iwbs)
  (cpp-new-method type name params)
  )

(defun cpp-new-pro-method (type name params)
  "Create a new protected method"
  (interactive "sType: \nsName: \nsParameters")
  (find-file cpp-global-hdr-name)
  (goto-char (point-min))
  (search-forward "protected: // METHODS")
  (forward-line 1)
  (insert (concat " " type " " name " (" params ");\n"))
  (cpp-iwbs)
  (cpp-new-method type name params)
  )

(defun cpp-new-pri-member (type mname)
  "Create a new private member"
  (interactive "sType: \nsName: ")
  (find-file cpp-global-hdr-name)
  (goto-char (point-min))
  (search-forward "private: // MEMBERS")
  (forward-line 1)
  (setq tstr (concat "m" (capitalize mname)))
  (insert (concat " " type " " tstr ";\n"))
  (cpp-iwbs)
  )

(defun cpp-new-pri-member-accessors (type mname)
  "Create a new private member with public accessors"
  (interactive "sType: \nsName: ")
  (cpp-new-pri-member type mname)
  (cpp-new-pub-method "void" (concat "Set" (capitalize mname)) type)
  (cpp-new-pub-method type (capitalize mname) " ")
  (cpp-iwbs)
  )

(defun cpp-new-pro-member (type mname)
  "Create a new protected member"
  (interactive "sType: \nsName: ")
  (find-file cpp-global-hdr-name)
  (goto-char (point-min))
  (search-forward "protected: // MEMBERS")
  (forward-line 1)
  (setq tstr (concat "m" (capitalize mname)))
  (insert (concat " " type " " tstr ";\n"))
  (cpp-iwbs)
  )

(defun cpp-new-pub-member (type mname)
  "Create a new public member"
  (interactive "sType: \nsName: ")
  (find-file cpp-global-hdr-name)
  (goto-char (point-min))
  (search-forward "public: // MEMBERS")
  (forward-line 1)
  (setq tstr (concat "m" (capitalize mname)))
  (insert (concat " " type " " tstr ";\n"))
  (cpp-iwbs)
  )

;;(defun cpp-context (classname namespace)
(defun cpp-context (classname)
  "Set the global context for the class"
  (interactive "sClassname: ")
  (setq cpp-global-classname (capitalize classname))
  (setq cpp-global-uclassname (upcase classname))
  (setq cpp-global-hdr-name (concat cpp-global-classname cpp-global-hdr-postfix))
  (setq cpp-global-impl-name (concat cpp-global-classname cpp-global-impl-postfix))
  (setq cpp-global-testhdr-name (concat "xxxTest_" cpp-global-classname cpp-global-hdr-postfix))
  (setq cpp-global-testclassname (concat cpp-global-classname "TestSuite"))
  (find-file cpp-global-hdr-name)
  (find-file cpp-global-impl-name)
  (set-window-buffer (frame-first-window) cpp-global-hdr-name)
  (goto-char (point-min))
  ;;(find-file cpp-global-impl-name)
  (set-window-buffer (next-window) cpp-global-impl-name)
  (goto-char (point-min))
  )

;;(defun cpp-class (classname namespace)
(defun cpp-class (classname)
  "Create a new C++ class"
  (interactive "sClassname: ")
  (cpp-context classname)
  (cpp-hdr)
  (cpp-impl)
  (cpp-test-hdr)
  (cpp-new-structors classname)
  (cpp-context classname)
  )

;; (setq cpp-left-window (frame-first-window))
;; (setq cpp-right-window (next-window))
(global-set-key (kbd "\C-c c") 'cpp-class)
(global-set-key (kbd "\C-c x") 'cpp-context)
(global-set-key (kbd "\C-c m r") 'cpp-new-pri-member)
(global-set-key (kbd "\C-c m a") 'cpp-new-pri-member-accessors)
(global-set-key (kbd "\C-c m o") 'cpp-new-pro-member)
(global-set-key (kbd "\C-c m p") 'cpp-new-pub-member)
(global-set-key (kbd "\C-c f p") 'cpp-new-pub-method)
(global-set-key (kbd "\C-c f r") 'cpp-new-pri-method)
(global-set-key (kbd "\C-c f o") 'cpp-new-pro-method)
(global-set-key (kbd "\C-c i h") 'cpp-protected-hdr-inclusion)
(global-set-key (kbd "\C-c i c") 'cpp-protected-impl-inclusion)

(provide 'cppgen)