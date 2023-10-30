import QtQuick
import QtQuick.Controls
import Qt5Compat.GraphicalEffects
import QtExtensions.Toolkit

FluentRectangle {
    id: control
    color: "#00000000"
    layer.enabled: true
    layer.effect: OpacityMask {
        maskSource: ShaderEffectSource{
            sourceItem: FluentRectangle {
                radius: control.radius
                width: control.width
                height: control.height
            }
        }
    }
}