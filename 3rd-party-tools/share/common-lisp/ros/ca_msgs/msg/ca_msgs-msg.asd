
(cl:in-package :asdf)

(defsystem "ca_msgs-msg"
  :depends-on (:roslisp-msg-protocol :roslisp-utils :std_msgs-msg
)
  :components ((:file "_package")
    (:file "ChargingState" :depends-on ("_package_ChargingState"))
    (:file "_package_ChargingState" :depends-on ("_package"))
    (:file "Mode" :depends-on ("_package_Mode"))
    (:file "_package_Mode" :depends-on ("_package"))
    (:file "Bumper" :depends-on ("_package_Bumper"))
    (:file "_package_Bumper" :depends-on ("_package"))
  ))