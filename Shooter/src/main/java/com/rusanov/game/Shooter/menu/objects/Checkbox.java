package com.rusanov.game.Shooter.menu.objects;

import com.rusanov.game.Shooter.game.Constants;
import com.rusanov.game.Shooter.Input;
import com.rusanov.game.Shooter.graphics.Draw;
import com.rusanov.game.Shooter.menu.MenuConstants;
import com.rusanov.game.Shooter.menu.MenuSizes;
import org.lwjgl.opengl.GL11;
import org.newdawn.slick.Color;
import org.newdawn.slick.TrueTypeFont;

public class Checkbox extends MenuObject {
    private boolean isSelected = false;
    private boolean isPressed = false;
    private String name;
    private TrueTypeFont font;
    private int textureFont;
    private int checkboxX;
    private int checkboxY;

    public Checkbox(String name, TrueTypeFont font, int textureFont, int x, int y) {
        this.name = name;
        this.font = font;
        this.textureFont = textureFont;
        width = MenuSizes.CHECKBOX_SIZE;
        this.x = x;
        this.y = y;
        checkboxX = x + font.getWidth(name) + width;
        checkboxY = y + font.getHeight() / 2;
        color = MenuConstants.BUTTON_ACTIVE_COLOR;
        transparency = MenuConstants.BUTTON_TRANSPARENCY;
    }

    @Override
    public void render() {
        Draw.text(textureFont, font, x, y, name, Color.black);

        GL11.glColor3ub((byte)Color.black.getRed(), (byte)Color.black.getGreen(), (byte)Color.black.getBlue());
        Draw.filledCircle(checkboxX, checkboxY, width, 16);
        GL11.glColor4ub((byte)color.getRed(), (byte)color.getGreen(), (byte)color.getBlue(), (byte)transparency);
        Draw.filledCircle(checkboxX, checkboxY, MenuSizes.CHECKBOX_DIAMETER_ACTIVE, 16);
        if (isSelected) {
            GL11.glColor3ub((byte)Color.black.getRed(), (byte)Color.black.getGreen(), (byte)Color.black.getBlue());
            Draw.filledCircle(checkboxX, checkboxY, MenuSizes.CHECKBOX_DIAMETER_SELECTED, 16);
        }
        GL11.glColor4f(1, 1, 1, 1);
    }

    @Override
    public void update() {
        int moutheX = Input.getMoutheX();
        int moutheY = Input.getMoutheY();
        if (moutheX >= checkboxX - width / 2 && moutheX <= checkboxX + width / 2 &&
                moutheY >= checkboxY - width / 2 && moutheY <= checkboxY + width / 2) {
            transparency = MenuConstants.BUTTON_TRANSPARENCY_SELECTED;
            if (Input.isMouseButtonClicked(Constants.MOUSE_LEFT)) {
                isSelected = !isSelected;
                isPressed = true;
            }
        } else {
            transparency = MenuConstants.BUTTON_TRANSPARENCY;
        }
    }

    public boolean isSelected() {
        return isSelected;
    }

    public void setSelected(boolean isSelected) {
        this.isSelected = isSelected;
    }

    public boolean isPressed() {
        return isPressed;
    }

    public void setNotPressed() {
        isPressed = false;
    }
}
