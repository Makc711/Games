package com.rusanov.game.Shooter.game.objects;

import com.rusanov.game.Shooter.game.Constants;
import com.rusanov.game.Shooter.graphics.GameTexture;
import org.lwjgl.opengl.GL11;

import java.awt.*;
import java.util.List;
import java.util.concurrent.ThreadLocalRandom;

public class Human extends GameObject {
    private GameTexture textureHuman;
    private int textureSize = Constants.HUMAN_TEXTURE_SIZE;
    private float angle = ThreadLocalRandom.current().nextInt(0, 360);
    private float fireCooldownTime = 0;
    private float speed = 0;

    Human(GameObjectType type, GameTexture textureHuman, Color color) {
        setType(type);
        setWidth(Constants.HUMAN_SIZE);
        setHeight(Constants.HUMAN_SIZE);
        this.textureHuman = textureHuman;
        setColor(color);
    }

    @Override
    public void render() {
        final float centerTX = (float)(textureSize / 2 -
                (double)Constants.HUMAN_GUN_SIZE * textureSize / (2 * textureHuman.getTextureWidth()));
        final float centerTY = textureSize / 2;
        GL11.glColor3ub((byte)getColor().getRed(), (byte)getColor().getGreen(), (byte)getColor().getBlue());
        textureHuman.draw(getX(), getY(), textureSize, textureSize, centerTX, centerTY, angle);
        GL11.glColor3f(1, 1, 1);
    }

    @Override
    public void update(float deltaTime) {
        super.update(deltaTime);
        if (fireCooldownTime > 0) {
            fireCooldownTime -= deltaTime;
        }
    }

    @Override
    public void intersect(GameObject otherObject) {

    }

    void move(Direction direction) {
        setXSpeed(0);
        setYSpeed(0);
        switch (direction) {
            case UP:
                setXSpeed((float)(speed * Math.cos(angle / 180 * Math.PI)));
                setYSpeed((float)(speed * -Math.sin(angle / 180 * Math.PI)));
                break;
            case DOWN:
                setXSpeed((float)(speed * -Math.cos(angle / 180 * Math.PI)));
                setYSpeed((float)(speed * Math.sin(angle / 180 * Math.PI)));
                break;
            case LEFT:
                setXSpeed((float)(speed * Math.cos((angle + 90) / 180 * Math.PI)));
                setYSpeed((float)(speed * -Math.sin((angle + 90) / 180 * Math.PI)));
                break;
            case RIGHT:
                setXSpeed((float)(speed * Math.cos((angle - 90) / 180 * Math.PI)));
                setYSpeed((float)(speed * -Math.sin((angle - 90) / 180 * Math.PI)));
                break;
            case UP_LEFT:
                setXSpeed((float)(speed * Math.cos((angle + 45) / 180 * Math.PI)));
                setYSpeed((float)(speed * -Math.sin((angle + 45) / 180 * Math.PI)));
                break;
            case UP_RIGHT:
                setXSpeed((float)(speed * Math.cos((angle - 45) / 180 * Math.PI)));
                setYSpeed((float)(speed * -Math.sin((angle - 45) / 180 * Math.PI)));
                break;
            case DOWN_LEFT:
                setXSpeed((float)(speed * Math.cos((angle + 135) / 180 * Math.PI)));
                setYSpeed((float)(speed * -Math.sin((angle + 135) / 180 * Math.PI)));
                break;
            case DOWN_RIGHT:
                setXSpeed((float)(speed * Math.cos((angle - 135) / 180 * Math.PI)));
                setYSpeed((float)(speed * -Math.sin((angle - 135) / 180 * Math.PI)));
                break;
            default:
                System.out.println("Error: non-existent direction \"" + direction.name() + "\"!");
        }
    }

    boolean fire() {
        if (fireCooldownTime > 0) {
            return false;
        }
        fireCooldownTime = Constants.HUMAN_FIRE_COOLDOWN_TIME;
        float[] position = calculateFrontCellPosition();
        float x = position[0];
        float y = position[1];
        float xSpeed = (float)(Constants.BULLET_SPEED * Math.cos(angle / 180 * Math.PI));
        float ySpeed = (float)(Constants.BULLET_SPEED * -Math.sin(angle / 180 * Math.PI));
        Bullet bullet = (Bullet)getGame().createObject(GameObjectType.BULLET, x, y);
        if (bullet != null) {
            bullet.setOwnerObject(this);
            bullet.setColor(getColor());
            bullet.setXSpeed(xSpeed);
            bullet.setYSpeed(ySpeed);
            return true;
        }
        return false;
    }

    private float[] calculateFrontCellPosition() {
        float radius = (float)(textureSize / 2 +
                (double)Constants.HUMAN_GUN_SIZE * textureSize / (2 * textureHuman.getTextureWidth())) + Constants.BULLET_SIZE / 2;
        float x = getX() + (float)Math.cos(angle / 180 * Math.PI) * radius;
        float y = getY() + (float)-Math.sin(angle / 180 * Math.PI) * radius;
        return new float[]{x, y};
    }

    float[] distanceTo(GameObjectType humanType) {
        float[] position = calculateFrontCellPosition();
        float x = position[0];
        float y = position[1];
        GameObject targetObject = checkIntersectsWithBullet(x, y);
        GameObjectType targetObjectType;
        if (targetObject != null) {
            targetObjectType = targetObject.getType();
        } else {
            targetObjectType = GameObjectType.NONE;
        }
        float distanceToHuman = 0;
        float distanceToBlock = 0;
        float distanceToHumanBullet = 0;
        int kX = 1;
        int kY = 1;
        while (targetObject == null || targetObjectType != humanType) {
            int x00 = (int)x - Constants.BULLET_SIZE / 2;
            int y00 = (int)y - Constants.BULLET_SIZE / 2;
            int x01 = x00 + Constants.BULLET_SIZE - 1;
            int y01 = y00 + Constants.BULLET_SIZE - 1;
            if (targetObject == this || x00 < 0 || y00 < 0 || x01 >= Constants.SCREEN_WIDTH || y01 >= Constants.SCREEN_HEIGHT) {
                distanceToHuman = -1;
                break;
            }

            if (targetObjectType == GameObjectType.BLOCK) {
                int x10 = (int)targetObject.getX() - targetObject.getWidth() / 2;
                int y10 = (int)targetObject.getY() - targetObject.getHeight() / 2;
                int x11 = x10 + targetObject.getWidth() - 1;
                int y11 = y10 + targetObject.getHeight() - 1;

                if (x00 >= x11 || x01 <= x10) {
                    kX *= -1;
                } else if (y00 >= y11 || y01 <= y10) {
                    kY *= -1;
                }

                if (distanceToBlock == 0) {
                    distanceToBlock = distanceToHuman;
                }
            } else if (targetObjectType == GameObjectType.BULLET) {
                Bullet bullet = (Bullet)targetObject;
                if (distanceToHumanBullet == 0 && bullet.getOwnerObject().getType() == humanType) {
                    distanceToHumanBullet = distanceToHuman;
                }
            }

            float oldX = x;
            float oldY = y;
            x += (float)(Math.cos(angle / 180 * Math.PI) * kX);
            y += (float)(-Math.sin(angle / 180 * Math.PI) * kY);
            float dX = Math.abs(x - oldX);
            float dY = Math.abs(y - oldY);
            distanceToHuman += (float)Math.sqrt(dX * dX + dY * dY);
            if (distanceToHuman > Constants.MAXIMUM_FIRE_DISTANCE) {
                distanceToHuman = -1;
                break;
            }

            targetObject = checkIntersectsWithBullet(x, y);
            if (targetObject != null) {
                targetObjectType = targetObject.getType();
            } else {
                targetObjectType = GameObjectType.NONE;
            }
        }
        return new float[]{distanceToHuman, distanceToBlock, distanceToHumanBullet};
    }

    @SuppressWarnings("all")
    private GameObject checkIntersectsWithBullet(float x, float y) {
        int x00 = (int)x - Constants.BULLET_SIZE / 2;
        int y00 = (int)y - Constants.BULLET_SIZE / 2;
        int x01 = x00 + Constants.BULLET_SIZE - 1;
        int y01 = y00 + Constants.BULLET_SIZE - 1;

        List<GameObject> objectsOnLevel = getGame().getObjects();
        for (GameObject object : objectsOnLevel) {
            int x10 = (int)object.getX() - object.getWidth() / 2;
            int y10 = (int)object.getY() - object.getHeight() / 2;
            int x11 = x10 + object.getWidth() - 1;
            int y11 = y10 + object.getHeight() - 1;

            if (x00 <= x11 && x01 >= x10 && y00 <= y11 && y01 >= y10) {
                return object;
            }
        }
        return null;
    }

    void setSpeed(float speed) {
        this.speed = speed;
    }

    float getAngle() {
        return angle;
    }

    void setAngle(float angle) {
        this.angle = angle;
    }
}
