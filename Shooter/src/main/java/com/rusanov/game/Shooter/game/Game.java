package com.rusanov.game.Shooter.game;

import com.rusanov.game.Shooter.Input;
import com.rusanov.game.Shooter.graphics.GameTexture;
import com.rusanov.game.Shooter.menu.*;
import com.rusanov.game.Shooter.graphics.Window;
import com.rusanov.game.Shooter.game.objects.*;
import com.rusanov.game.Shooter.game.objects.LieAlgorithm.WayFinder;
import org.lwjgl.Sys;
import org.lwjgl.input.Keyboard;
import org.lwjgl.opengl.Display;
import org.lwjgl.opengl.GL11;
import org.newdawn.slick.TrueTypeFont;

import java.awt.*;
import java.util.ArrayList;
import java.util.List;
import java.util.concurrent.ThreadLocalRandom;

public class Game {
    private boolean isGameActive = true;
    private long timeLastFrame = 0;
    private List<GameObject> objects;
    private GameTexture textureHuman;
    private WayFinder wayFinder;
    private GameObject player;
    private GameObject enemy;
    private int playerPoints = 0;
    private int enemyPoints = 0;
    private TrueTypeFont timesNewRoman;
    private int textureFont;
    private boolean isPlayerDied = false;
    private boolean isEnemyDied = false;
    private boolean isReload = false;
    private GameState gameState = GameState.MENU;
    private GameState gameStateOld = null;
    private MenuConstructor menuConstructor;
    private PauseMenu pauseMenu;

    public enum GameState {
        MENU, PLAY, PAUSE
    }

    void setupSystem() {
        new Window(Constants.SCREEN_WIDTH, Constants.SCREEN_HEIGHT, Constants.SCREEN_NAME, Constants.FULLSCREEN);
        textureHuman = new GameTexture("Textures/Human.png");
        Font awtFont = new Font("Times New Roman", Font.BOLD, Constants.FONT_SIZE);
        textureFont = GL11.glGenTextures() + 1;
        timesNewRoman = new TrueTypeFont(awtFont, true);
        menuConstructor = new MenuConstructor(this);
        pauseMenu = new PauseMenu(this);
    }

    public void initialize() {
        objects = new ArrayList<>();
        new Level(this);
        wayFinder = new WayFinder(objects);
        timeBetweenFrames();
    }

    boolean loop() {
        if (Display.isCloseRequested() || isReload) {
            return false;
        }
        float deltaTime = timeBetweenFrames();

        GL11.glClear(GL11.GL_COLOR_BUFFER_BIT);
        GL11.glLoadIdentity();
        switch (gameState) {
            case MENU:
                setCursor("Textures/CursorHand.png", 3, 26);
                menuConstructor.render();
                menuConstructor.update();
                break;
            case PLAY:
                setCursor("Textures/CursorAim.png", 16, 16);
                render();
                update(deltaTime);
                break;
            case PAUSE:
                setCursor("Textures/CursorHand.png", 3, 26);
                render();
                pauseMenu.render();
                pauseMenu.update();
                break;
            default:
                System.err.println("Error: Unknown game state \"" + gameState + "\"!");
                return false;
        }
        updateDisplay();

        return isGameActive;
    }

    private void setCursor(String imageName, int xHotSpot, int yHotSpot) {
        if (gameStateOld != gameState) {
            gameStateOld = gameState;
            Input.setCursor(imageName, xHotSpot, yHotSpot);
        }
    }

    private void updateDisplay() {
        Display.update();
        Display.sync(Constants.FPS);
    }

    private float timeBetweenFrames() {
        long time = getTimeMS();
        float deltaTime = (float)(time - timeLastFrame) / 1000;
        timeLastFrame = time;
        return deltaTime;
    }

    private static long getTimeMS() {
        return Sys.getTime() * 1000 / Sys.getTimerResolution();
    }

    void shutdown() {
        Display.destroy();
    }

    private void render() {
        for (GameObject object : objects) {
            object.render();
        }
        drawText();
    }

    private void drawText() {
        GL11.glEnable(GL11.GL_TEXTURE_2D);
        GL11.glBindTexture(GL11.GL_TEXTURE_2D, textureFont);

        String scorePlayer = String.valueOf(playerPoints);
        int scorePlayerWidth = timesNewRoman.getWidth(scorePlayer);
        timesNewRoman.drawString(Constants.SCORE_POSITION_X, Constants.SCORE_POSITION_Y, scorePlayer, org.newdawn.slick.Color.green);
        String delimeter = " : ";
        int delimeterWidth = timesNewRoman.getWidth(delimeter);
        timesNewRoman.drawString(Constants.SCORE_POSITION_X + scorePlayerWidth,
                Constants.SCORE_POSITION_Y, delimeter, org.newdawn.slick.Color.black);
        timesNewRoman.drawString(Constants.SCORE_POSITION_X + scorePlayerWidth + delimeterWidth,
                Constants.SCORE_POSITION_Y, String.valueOf(enemyPoints), org.newdawn.slick.Color.red);

        boolean isContinue = false;
        if (player != null && player.getHealth() <= 0) {
            String playerDied = "Player died!";
            timesNewRoman.drawString(Constants.SCREEN_WIDTH / 2 - timesNewRoman.getWidth(playerDied) / 2,
                    Constants.SCREEN_HEIGHT / 2 - timesNewRoman.getHeight(playerDied) / 2, playerDied, org.newdawn.slick.Color.green);
            isContinue = true;
        }
        if (enemy != null && enemy.getHealth() <= 0) {
            String enemyDied = "Enemy died!";
            timesNewRoman.drawString(Constants.SCREEN_WIDTH / 2 - timesNewRoman.getWidth(enemyDied) / 2,
                    Constants.SCREEN_HEIGHT / 2 + timesNewRoman.getHeight(enemyDied) / 2, enemyDied, org.newdawn.slick.Color.red);
            isContinue = true;
        }
        if (isContinue) {
            String pressSpace = "Press SPACE to continue...";
            timesNewRoman.drawString(Constants.SCREEN_WIDTH / 2 - timesNewRoman.getWidth(pressSpace) / 2,
                    Constants.SCREEN_HEIGHT - timesNewRoman.getHeight(pressSpace) *4 , pressSpace, org.newdawn.slick.Color.black);
        }
        if (playerPoints >= Constants.MAX_SCORE && enemyPoints < Constants.MAX_SCORE) {
            String playerWin = "YOU ARE WIN!!!";
            timesNewRoman.drawString(Constants.SCREEN_WIDTH / 2 - timesNewRoman.getWidth(playerWin) / 2,
                    timesNewRoman.getHeight(playerWin) *4 , playerWin, org.newdawn.slick.Color.green);
        } else if (enemyPoints >= Constants.MAX_SCORE && playerPoints < Constants.MAX_SCORE) {
            String playerLoose = "YOU ARE LOOSE...";
            timesNewRoman.drawString(Constants.SCREEN_WIDTH / 2 - timesNewRoman.getWidth(playerLoose) / 2,
                    timesNewRoman.getHeight(playerLoose) *4 , playerLoose, org.newdawn.slick.Color.red);
        }
        if (playerPoints >= Constants.MAX_SCORE && enemyPoints >= Constants.MAX_SCORE) {
            String deadHeat = "DEAD HEAT...";
            timesNewRoman.drawString(Constants.SCREEN_WIDTH / 2 - timesNewRoman.getWidth(deadHeat) / 2,
                    timesNewRoman.getHeight(deadHeat) *4 , deadHeat, org.newdawn.slick.Color.blue);
        }

        GL11.glBindTexture(GL11.GL_TEXTURE_2D, 0);
        GL11.glDisable(GL11.GL_TEXTURE_2D);
    }

    private void update(float deltaTime) {
        if (Input.isKeyClicked(Keyboard.KEY_ESCAPE)) {
            gameState = GameState.PAUSE;
        }

        List<GameObject> currentObjects = new ArrayList<>(objects);
        for (GameObject object : currentObjects) {
            object.update(deltaTime);
            if (object.getHealth() <= 0) {
                destroyObject(object);
            }
        }

        if (player != null && player.getHealth() <= 0 && !isPlayerDied) {
            enemyPoints++;
            isPlayerDied = true;
        }
        if (enemy != null && enemy.getHealth() <= 0 && !isEnemyDied) {
            playerPoints++;
            isEnemyDied = true;
        }

        if (isPlayerDied || isEnemyDied) {
            if (Keyboard.isKeyDown(Keyboard.KEY_SPACE)) {
                if (playerPoints >= Constants.MAX_SCORE || enemyPoints >= Constants.MAX_SCORE) {
                    resetGameProgress();
                    gameState = GameState.MENU;
                } else {
                    isPlayerDied = false;
                    isEnemyDied = false;
                    initialize();
                }
            }
        }
    }

    private void resetGameProgress() {
        Input.keyboardRefresh();
        isPlayerDied = false;
        isEnemyDied = false;
        playerPoints = 0;
        enemyPoints = 0;
    }

    public GameObject createObject(GameObjectType objectType, float x, float y) {
        GameObject object = null;

        switch (objectType) {
            case BLOCK:
                int width = ThreadLocalRandom.current().nextInt(Constants.BLOCK_SIZE_MIN, Constants.BLOCK_SIZE_MAX + 1);
                int height = ThreadLocalRandom.current().nextInt(Constants.BLOCK_SIZE_MIN, Constants.BLOCK_SIZE_MAX + 1);
                object = new Block(width + 2 * Constants.HUMAN_SIZE, height + 2 * Constants.HUMAN_SIZE);
                if (!moveObjectTo(object, x, y)) {
                    return null;
                } else {
                    object.setWidth(width);
                    object.setHeight(height);
                }
                break;
            case PLAYER:
                object = new Player(textureHuman);
                break;
            case ENEMY:
                object = new Enemy(textureHuman);
                break;
            case BULLET:
                object = new Bullet();
                break;
            default:
                System.out.println("Error: Can't create object \"" + objectType.name() + "\"");
        }

        if (object == null || !moveObjectTo(object, x, y)) {
            return null;
        }

        object.setGame(this);

        objects.add(object);
        return object;
    }

    private void destroyObject(GameObject object) {
        objects.remove(object);
    }

    public boolean moveObjectTo(GameObject object, float x, float y) {
        int x0 = (int)x - object.getWidth() / 2;
        int y0 = (int)y - object.getHeight() / 2;
        int x1 = x0 + object.getWidth() - 1;
        int y1 = y0 + object.getHeight() - 1;

        if ( x0 < 0 || y0 < 0 || x1 >= Constants.SCREEN_WIDTH || y1 >= Constants.SCREEN_HEIGHT) {
            if (object.getType() == GameObjectType.BULLET) {
                object.setHealth(0);
            }
            return false;
        }

        boolean canMoveToCell = false;
        GameObject otherObject = checkIntersects(x, y, object);

        if (otherObject != null) {
            object.intersect(otherObject);
        } else {
            canMoveToCell = true;
        }

        if (canMoveToCell) {
            object.setX(x);
            object.setY(y);
        }

        return canMoveToCell;
    }

    @SuppressWarnings("all")
    private GameObject checkIntersects(float x, float y, GameObject exceptObject) {
        int x00 = (int)x - exceptObject.getWidth() / 2;
        int y00 = (int)y - exceptObject.getHeight() / 2;
        int x01 = x00 + exceptObject.getWidth() - 1;
        int y01 = y00 + exceptObject.getHeight() - 1;

        for (GameObject object : objects) {
            if (object != exceptObject) {
                int x10 = (int)object.getX() - object.getWidth() / 2;
                int y10 = (int)object.getY() - object.getHeight() / 2;
                int x11 = x10 + object.getWidth() - 1;
                int y11 = y10 + object.getHeight() - 1;

                if (x00 <= x11 && x01 >= x10 && y00 <= y11 && y01 >= y10) {
                    return object;
                }
            }
        }
        return null;
    }

    public List<GameObject> getObjects() {
        return objects;
    }

    public WayFinder getWayFinder() {
        return wayFinder;
    }

    public GameObject getPlayer() {
        return player;
    }

    void setPlayer(GameObject player) {
        this.player = player;
    }

    void setEnemy(GameObject enemy) {
        this.enemy = enemy;
    }

    public void setGameState(GameState gameState) {
        this.gameState = gameState;
    }

    public void exit() {
        isGameActive = false;
    }

    boolean isReload() {
        return isReload;
    }

    public void reload() {
        isReload = true;
    }
}
