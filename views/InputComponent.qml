import QtQuick
import QtQuick.Controls

import "js/validate.js" as InputValidator

Item{
    id:control
    property string placeholder
    property string label
    property bool phonenumberInput: false
    property bool usernameInput: false
    property bool emailInput:false
    property string icon_path
    property string text: text_field.text
    property bool good_data: false

    function clearField(){
        text_field.text = "";
        control.icon_path = "";
        good_data = false;
    }

    Column{
        anchors.fill: parent

        Rectangle{
            color: "#00000000"
            width:parent.width
            height:parent.height*0.5

            Text{
                color:'white'
                text:control.label
                font.pixelSize: Math.min(parent.height,parent.width)/2
            }
        }

        Row{
            width:parent.width
            height:parent.height*0.5

            Rectangle{
                color: "#00000000"
                width:parent.width
                height:parent.height

                TextField{
                    id: text_field
                    color:'white'
                    placeholderText: control.placeholder
                    placeholderTextColor: 'gray'
                    anchors.fill:parent
                    font.pixelSize: Math.min(parent.height,parent.width)/2.5
                    leftPadding: 10
                    verticalAlignment: TextInput.AlignVCenter

                    validator: RegularExpressionValidator {
                        regularExpression:{
                            switch(true){
                            case(control.usernameInput) : return /^[A-Za-z0-9_]{20}$/;
                            case (control.phonenumberInput): return /^[0-9]{9}$/;
                            case(control.emailInput):return /^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,}$/;
                            default: return /^.+$/;
                            }
                        }
                    }

                    background: Rectangle{
                        border.color: 'white'
                        border.width: 1
                        radius:5
                        color: "#00000000"
                    }

                    onTextChanged: {

                        if(text_field.text === ""){
                            control.icon_path = "";
                            return;
                        }

                        if(InputValidator.validateData(text_field.text,control.phonenumberInput,control.usernameInput,control.emailInput,QmlDto)){

                            control.icon_path = "imgs/svg/check.svg";
                            control.good_data = true;
                        }
                        else{
                            control.good_data = false;
                            control.icon_path = "imgs/svg/wrong.svg";
                        }
                    }
                }
            }

            Rectangle{
                color: "#00000000"
                height:parent.height
                width:parent.width*0.1
                antialiasing:true

                Image {
                    source: control.icon_path
                    anchors.fill: parent
                    fillMode: Image.PreserveAspectFit
                }
            }
        }
    }
}
