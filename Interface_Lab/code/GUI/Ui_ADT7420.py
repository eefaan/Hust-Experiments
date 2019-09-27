# -*- coding: utf-8 -*-

# Form implementation generated from reading ui file './ADT7420.ui'
#
# Created by: PyQt5 UI code generator 5.6
#
# WARNING! All changes made in this file will be lost!

from PyQt5 import QtCore, QtGui, QtWidgets

class Ui_MplMainWindow(object):
    def setupUi(self, MplMainWindow):
        MplMainWindow.setObjectName("MplMainWindow")
        MplMainWindow.resize(572, 486)
        sizePolicy = QtWidgets.QSizePolicy(QtWidgets.QSizePolicy.Expanding, QtWidgets.QSizePolicy.Expanding)
        sizePolicy.setHorizontalStretch(0)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(MplMainWindow.sizePolicy().hasHeightForWidth())
        MplMainWindow.setSizePolicy(sizePolicy)
        MplMainWindow.setFocusPolicy(QtCore.Qt.TabFocus)
        self.gridLayout = QtWidgets.QGridLayout(MplMainWindow)
        self.gridLayout.setObjectName("gridLayout")
        self.label_2 = QtWidgets.QLabel(MplMainWindow)
        self.label_2.setAlignment(QtCore.Qt.AlignRight|QtCore.Qt.AlignTrailing|QtCore.Qt.AlignVCenter)
        self.label_2.setObjectName("label_2")
        self.gridLayout.addWidget(self.label_2, 6, 0, 1, 1)
        self.label_3 = QtWidgets.QLabel(MplMainWindow)
        self.label_3.setAlignment(QtCore.Qt.AlignRight|QtCore.Qt.AlignTrailing|QtCore.Qt.AlignVCenter)
        self.label_3.setObjectName("label_3")
        self.gridLayout.addWidget(self.label_3, 7, 0, 1, 1)
        self.label_4 = QtWidgets.QLabel(MplMainWindow)
        self.label_4.setAlignment(QtCore.Qt.AlignRight|QtCore.Qt.AlignTrailing|QtCore.Qt.AlignVCenter)
        self.label_4.setObjectName("label_4")
        self.gridLayout.addWidget(self.label_4, 8, 0, 1, 1)
        self.label = QtWidgets.QLabel(MplMainWindow)
        self.label.setAlignment(QtCore.Qt.AlignRight|QtCore.Qt.AlignTrailing|QtCore.Qt.AlignVCenter)
        self.label.setObjectName("label")
        self.gridLayout.addWidget(self.label, 5, 0, 1, 1)
        self.mplfigure = MplWidget(MplMainWindow)
        self.mplfigure.setObjectName("mplfigure")
        self.gridLayout.addWidget(self.mplfigure, 0, 0, 4, 5)
        self.temp_target = QtWidgets.QLabel(MplMainWindow)
        self.temp_target.setObjectName("temp_target")
        self.gridLayout.addWidget(self.temp_target, 5, 1, 1, 1)
        self.textEdit_log = QtWidgets.QPlainTextEdit(MplMainWindow)
        self.textEdit_log.setReadOnly(True)
        self.textEdit_log.setObjectName("textEdit_log")
        self.gridLayout.addWidget(self.textEdit_log, 5, 4, 4, 1)
        self.temp_cur = QtWidgets.QLabel(MplMainWindow)
        self.temp_cur.setObjectName("temp_cur")
        self.gridLayout.addWidget(self.temp_cur, 6, 1, 1, 1)
        self.door_num = QtWidgets.QLabel(MplMainWindow)
        self.door_num.setObjectName("door_num")
        self.gridLayout.addWidget(self.door_num, 7, 1, 1, 1)
        self.fan_level = QtWidgets.QLabel(MplMainWindow)
        self.fan_level.setObjectName("fan_level")
        self.gridLayout.addWidget(self.fan_level, 8, 1, 1, 1)

        self.retranslateUi(MplMainWindow)
        QtCore.QMetaObject.connectSlotsByName(MplMainWindow)

    def retranslateUi(self, MplMainWindow):
        _translate = QtCore.QCoreApplication.translate
        MplMainWindow.setWindowTitle(_translate("MplMainWindow", "ADT7410"))
        self.label_2.setText(_translate("MplMainWindow", "采样温度："))
        self.label_3.setText(_translate("MplMainWindow", "门窗打开数："))
        self.label_4.setText(_translate("MplMainWindow", "风扇档位："))
        self.label.setText(_translate("MplMainWindow", "目标温度："))
        self.temp_target.setText(_translate("MplMainWindow", "36℃"))
        self.temp_cur.setText(_translate("MplMainWindow", "0℃"))
        self.door_num.setText(_translate("MplMainWindow", "0"))
        self.fan_level.setText(_translate("MplMainWindow", "8"))

from mplwidget import MplWidget
