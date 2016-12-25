#lang racket

(define pwd (current-directory))
(define folders (directory-list pwd))
(println folders)
