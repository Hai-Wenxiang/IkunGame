#include "scene.h"

/* ��������λ�ú����Ӻţ��õ�box���� */
static unsigned short getBoxType(int row, int col, int seed, unsigned short kindBase)
{
	unsigned short base = kindBase;
	unsigned short kind = rand() % 3;
	if (kind > 0) {
		kind = (kind << 1) - 1;
	}
	return (unsigned short)(base | kind);
}

static bool canMoveTo(Box* box)
{
	return box->isPlain();
}

/* ��ֹ�ڿ�ʼ��ʱ���ɫ����ֵ�λ�� */
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

	switch (welcomeMode) {
	case 0:
		type = GAME;
		role = Role();
		rolePos.x = rolePos.y = gameWidth >> 1;
		roleState = 0;
		seed = rand();
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

/* �ھ��ɫ��ǰ�ķ��� */
void Scene::dig(void)
{
	getTowardBox()->dig();
	return;
}

/* �ж������Ƿ��ʰȡ */
bool Scene::canFetch(Box box)
{
	// �ж����鱾���Ƿ��ʰȡ
	if (!box.canFetch()) {
		return false;
	}

	// �ж�����״̬����������������������

	return true;
}

/* ʰȡ��ǰ�ķ������� */
void Scene::fetch(void)
{
	Box* towardBox = getTowardBox();
	if (!canFetch(*towardBox)) {
		return;
	}

	// �Ž�����

	// ��ոø�
	towardBox->setPlain();
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
	// ���������ƶ�
	case 'a':
	case 'w':
	case 'd':
	case 's':
		move(key);
		break;

	// �ھ򷽿�
	case 'e':
		dig();
		break;

	// ʰȡ����
	case 'f':
		fetch();
		break;

	// �˳���Ϸ
	case ESC:
		exitGame();
		break;

	// δ֪�����Ͳ�����
	default:
		break;
	}
	return;
}

/* ����������ַ������˳���Ϸ�򷵻�false */
void Scene::parseKey(int key)
{
	std::cout << key << std::endl;
	if (key == -1) {
		return;
	}

	std::thread music(playOnce, JI);
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
	cv::ellipse(mat, cv::Point(width >> 1, 350 + welcomeMode * 180), cv::Size(300, 80), 0, 0, 360, cv::Scalar(0, 0, 0), 3);
	return mat;
}

cv::Mat Scene::getMatInSetFPS(void)
{
	cv::Mat mat = getSetFPSMat().clone();
	cv::ellipse(mat, cv::Point(width >> 1, 325 + fpsMode * 180), cv::Size(200, 60), 0, 0, 360, cv::Scalar(0, 0, 0), 3);
	return mat;
}

void Scene::addMap(cv::Mat mat)
{
	cv::Point point1, rolePoint;
	cv::Mat roleMat = role.getMat();

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
	cv::Mat mat = cv::Mat(height, width, CV_8UC3, cv::Scalar(100, 100, 100));
	addMap(mat);
	addState(mat);
	return mat;
}

Scene::Scene(void)
{
	fps = (unsigned short)25;				// ֡�ʳ�ʼΪ25
	width = (unsigned short)1260;
	height = (unsigned short)800;
	gameWidth = (unsigned int)1001;
	seeRows = (unsigned char)11;
	seeCols = (unsigned char)21;
	type = WELCOME;							// ��ʼ�ڻ�ӭ����
	welcomeMode = 0;
	fpsMode = 0;
	state = 0;
	role = Role();
	rolePos.x = rolePos.y = gameWidth >> 1;	// ��ɫ��ʼ������
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

/* �ж��Ƿ��˳���Ϸ */
bool Scene::notExitGame(int key)
{
	return type != WELCOME || key != ESC;
}

void Scene::parse(int key)
{
	parseKey(key);
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
		return cv::imread("pictures/default.png");
	}
}