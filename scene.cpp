#include "scene.h"

/* 根据所在位置和种子号，得到box种类 */
static unsigned short getBoxType(int row, int col, int seed, unsigned short kindBase)
{
	std::random_device randNum;
	unsigned short base = kindBase;
	unsigned short kind = randNum() % 3;
	if (kind > 0) {
		kind = (kind << 1) - 1;
	}
	return (unsigned short)(base | kind);
}

static bool canMoveTo(Box* box)
{
	return box->isPlain();
}

/* 防止在开始的时候角色在奇怪的位置 */
static void fixBeginRoleBox(Box** role)
{
	if (!canMoveTo(*role)) {
		delete *role;
		*role = new Box(WATER_PLAIN);
	}
	return;
}

static Box*** newBoxes(int seed, int gameWidth)
{
	Box*** boxes = new Box * *[gameWidth];
	for (int i = 0; i < gameWidth; i++) {
		boxes[i] = new Box * [gameWidth];
		for (int j = 0; j < gameWidth; j++) {
			boxes[i][j] = new Box(getBoxType(i, j, seed, (unsigned short)0));
		}
	}
	fixBeginRoleBox(boxes[gameWidth >> 1] + (gameWidth >> 1));
	return boxes;
}

static void deleteBoxes(Box*** boxes, int gameWidth)
{
	if (boxes == NULL) {
		return;
	}
	for (int i = 0; i < gameWidth; i++) {
		for (int j = 0; j < gameWidth; j++) {
			delete boxes[i][j];
		}
		delete boxes[i];
	}
	delete boxes;
	return;
}

void Scene::parseKeyInWelcome(int key)
{
	if (key == 'w') {
		welcomeMode = (welcomeMode + 2) % 3;
		return;
	}

	if (key == 's') {
		welcomeMode = (welcomeMode + 1) % 3;
		return;
	}

	if (key != ENTER) {
		return;
	}

	std::random_device randNum;
	switch (welcomeMode) {
	case 0:
		type = GAME;
		role = Role();
		rolePos.x = rolePos.y = gameWidth >> 1;
		roleState = 0;
		seed = randNum();
		boxes = newBoxes(seed, gameWidth);
		bag = Bag();
		break;
	case 1:
		type = SEEBUTTON;
		break;
	case 2:
		fpsMode = fps / 50;
		type = SETFPS;
		break;
	default:
		break;
	}

	return;
}

void Scene::parseKeyInSetFPS(int key)
{
	switch (key) {
	case 'w':
		fpsMode = (fpsMode + 2) % 3;
		break;
	case 's':
		fpsMode = (fpsMode + 1) % 3;
		break;
	case ENTER:
		fps = 25 << fpsMode;
		std::cout << "fps = " << fps << std::endl;
	case ESC:
		type = WELCOME;
		break;
	default:
		break;
	}

	return;
}

void Scene::saveGame(void)
{
	return;
}

void Scene::move(int key)
{
	switch (key) {
	case 'a':
		if (role.getToward() != LEFT) {
			role.setToward(LEFT);
		}
		else if (rolePos.x > 0 && canMoveTo(boxes[rolePos.y][rolePos.x - 1])) {
			rolePos.x--;
		}
		break;
	case 'w':
		if (role.getToward() != UP) {
			role.setToward(UP);
		}
		else if (rolePos.y > 0 && canMoveTo(boxes[rolePos.y - 1][rolePos.x])) {
			rolePos.y--;
		}
		break;
	case 'd':
		if (role.getToward() != RIGHT) {
			role.setToward(RIGHT);
		}
		else if (rolePos.x < gameWidth - 1 && canMoveTo(boxes[rolePos.y][rolePos.x + 1])) {
			rolePos.x++;
		}
		break;
	case 's':
		if (role.getToward() != DOWN) {
			role.setToward(DOWN);
		}
		else if (rolePos.y < gameWidth - 1 && canMoveTo(boxes[rolePos.y + 1][rolePos.x])) {
			rolePos.y++;
		}
		break;
	default:
		break;
	}
	return;
}

Box* Scene::getTowardBox(void)
{
	switch (role.getToward()) {
	case LEFT:
		return rolePos.x > 0 ? boxes[rolePos.y][rolePos.x - 1] : NULL;
	case UP:
		return rolePos.y > 0 ? boxes[rolePos.y - 1][rolePos.x] : NULL;
	case RIGHT:
		return rolePos.x < gameWidth - 1 ? boxes[rolePos.y][rolePos.x + 1] : NULL;
	case DOWN:
		return rolePos.y < gameWidth - 1 ? boxes[rolePos.y + 1][rolePos.x] : NULL;
	default:
		break;
	}
	return NULL;
}

/* 挖掘角色面前的方块 */
void Scene::dig(void)
{
	getTowardBox()->dig();
	return;
}

/* Box内容变为Goods内容 */
static Goods box2Goods(Box box)
{
	Goods goods = Goods();
	switch (box.getType()) {
	case WATER_WOOD_01:
	case FOREST_WOOD_01:
	case DEEP_FOREST_WOOD_01:
		goods.setType(1);
		goods.setNum(1);
		break;
	default:
		break;
	}
	return goods;
}

/* 判定方块是否可拾取，若可取则放进背包并返回1 */
bool Scene::canFetch(Box box)
{
	// 判定方块本身是否可拾取
	if (!box.canFetch()) {
		return false;
	}

	// 判定背包状态、、、、、、、、、、、
	Goods goods = box2Goods(box);
	if (goods.getType() != 0 && bag.putGoodsIn(goods)) {
		return true;
	}

	return false;
}

/* 拾取面前的方块内容 */
void Scene::fetch(void)
{
	Box* towardBox = getTowardBox();

	// 放进背包
	if (canFetch(*towardBox)) {
		// 清空该格
		towardBox->setPlain();
	}
	return;
}

void Scene::exitGame(void)
{
	saveGame();
	type = WELCOME;
	deleteBoxes(boxes, gameWidth);
	boxes = NULL;
	bag.~Bag();
	return;
}

void Scene::parseKeyInGame(int key)
{
	switch (key) {
	// 上下左右移动
	case 'a':
	case 'w':
	case 'd':
	case 's':
		move(key);
		break;

	// 切换背包中的手持部分
	case 'q':
		bag.setAtHandLeft();
		break;
	case 'e':
		bag.setAtHandRight();
		break;

	// 整理背包
	case 't':
		bag.tidyUp();
		break;

	// 挖掘方块
	case 'r':
		dig();
		break;

	// 拾取方块
	case 'f':
		fetch();
		break;

	// 退出游戏
	case ESC:
		exitGame();
		break;

	// 未知按键就不管它
	default:
		break;
	}
	return;
}

/* 解析输入的字符，若退出游戏则返回false */
void Scene::parseKey(int key, std::set<unsigned long long> musicSet)
{
	std::cout << key << std::endl;
	if (key == -1) {
		return;
	}

	std::thread music(playOnce, JI, musicSet);
	music.detach();

	switch (type) {
	case WELCOME:
		parseKeyInWelcome(key);
		break;
	case 1://////////
		parseKeyInWelcome(key);
		break;
	case 2:
		parseKeyInSetFPS(key);
		break;
	case GAME:
		parseKeyInGame(key);
		break;
	default:
		break;
	}

	return;
}

void Scene::parseScene(void)
{
	return;
}

cv::Mat Scene::getMatInWelcome(void)
{
	cv::Mat mat = getWelcomeMat().clone();
	cv::ellipse(mat, cv::Point(width >> 1, 350 + welcomeMode * 180),
		cv::Size(300, 80), 0, 0, 360, cv::Scalar(0, 0, 0, 255), 3);
	return mat;
}

cv::Mat Scene::getMatInSetFPS(void)
{
	cv::Mat mat = getSetFPSMat().clone();
	cv::ellipse(mat, cv::Point(width >> 1, 325 + fpsMode * 180),
		cv::Size(200, 60), 0, 0, 360, cv::Scalar(0, 0, 0, 255), 3);
	return mat;
}

void Scene::addMap(cv::Mat mat)
{
	cv::Point point1, rolePoint;

	point1.x = rolePos.x - (seeCols >> 1);
	point1.y = rolePos.y - (seeRows >> 1);
	rolePoint.x = seeCols >> 1;
	rolePoint.y = seeRows >> 1;
	if (point1.x < 0) {
		rolePoint.x += point1.x;
		point1.x = 0;
	}
	else if (point1.x + seeCols - 1 >= gameWidth) {
		rolePoint.x += point1.x + seeCols - gameWidth;
		point1.x -= point1.x + seeCols - gameWidth;
	}
	if (point1.y < 0) {
		rolePoint.y += point1.y;
		point1.y = 0;
	}
	else if (point1.y + seeRows - 1 >= gameWidth) {
		rolePoint.y += point1.y + seeRows - gameWidth;
		point1.y -= point1.y + seeRows - gameWidth;
	}

	for (int i = 0; i < seeRows; i++) {
		for (int j = 0; j < seeCols; j++) {
			cv::Mat boxMat = boxes[point1.y + i][point1.x + j]->getMat();
			boxMat.copyTo(mat(cv::Rect(j * BOXWIDTH, i * BOXWIDTH, BOXWIDTH, BOXWIDTH)));
		}
	}

	role.getMat().copyTo(mat(cv::Rect(
		rolePoint.x * BOXWIDTH, rolePoint.y * BOXWIDTH, BOXWIDTH, BOXWIDTH)));
	return;
}

static void addRoleState(cv::Mat mat, Role role)
{
	return;
}

void Scene::addState(cv::Mat mat)
{
	addRoleState(mat, role);
	bag.paintBagInGame(mat);
	return;
}

cv::Mat Scene::getMatInGame(void)
{
	cv::Mat mat = cv::Mat(height, width, CV_8UC4, cv::Scalar(100, 100, 100, 255));
	addMap(mat);
	addState(mat);
	return mat;
}

Scene::Scene(void)
{
	fps = (unsigned short)25;				// 帧率初始为25
	width = (unsigned short)1260;
	height = (unsigned short)800;
	gameWidth = (unsigned int)1001;
	seeRows = (unsigned char)11;
	seeCols = (unsigned char)21;
	type = WELCOME;							// 初始在欢迎界面
	welcomeMode = 0;
	fpsMode = 0;
	state = 0;
	role = Role();
	rolePos.x = rolePos.y = gameWidth >> 1;	// 角色初始在中心
	roleState = 0;
	seed = 0;
	boxes = newBoxes(seed, gameWidth);
	return;
}

Scene::~Scene(void)
{
	deleteBoxes(boxes, gameWidth);
	boxes = NULL;
	bag.~Bag();
	return;
}

void Scene::setFps(unsigned short newFps)
{
	fps = newFps;
	return;
}

unsigned short Scene::getFps(void)
{
	return fps;
}

void Scene::setWidth(unsigned short newWidth)
{
	width = newWidth;
	return;
}

unsigned short Scene::getWidth(void)
{
	return width;
}

void Scene::setHeight(unsigned short newHeight)
{
	height = newHeight;
	return;
}

unsigned short Scene::getHeight(void)
{
	return height;
}

void Scene::setType(unsigned char newType)
{
	type = newType;
	return;
}

unsigned char Scene::getType(void)
{
	return type;
}

void Scene::setRolePos(cv::Point newPos)
{
	rolePos = newPos;
	return;
}

cv::Point Scene::getRolePos(void)
{
	return rolePos;
}

Box*** Scene::getBoxes(void)
{
	return boxes;
}

/* 判定是否退出游戏 */
bool Scene::notExitGame(int key)
{
	return type != WELCOME || key != ESC;
}

void Scene::parse(int key, std::set<unsigned long long> musicSet)
{
	parseKey(key, musicSet);
	parseScene();
	return;
}

cv::Mat Scene::getMat(void)
{
	switch (type) {
	case WELCOME:
		return getMatInWelcome();
	case 1:
		return getMatInWelcome();
	case SETFPS:
		return getMatInSetFPS();
	case GAME:
		return getMatInGame();
	default:
		return getDefaultMat();
	}
}
