#include "jetstory.h"

#define IMAGECLASS JetStoryImg
#define IMAGEFILE <JetStory/JetStory.iml>
#include <Draw/iml_source.h>

using namespace Upp;

bool left, right, up, down, fire;

bool MapCollision(Rect r)
{
	if(r.bottom < 0)
		return false;
	if(r.left < 0 || r.left >= BLOCKSIZE * 128)
		return true;
	r.right--;
	r.bottom--;
	r /= 16;
	for(int x = r.left; x <= r.right; x++)
		for(int y = r.top; y <= r.bottom; y++) {
			if(y >= 0 && y < 4 * 40 && x >= 0 && x < 4 * 128) {
				int q = jetstory[y >> 2][x >> 2];
				if(q && blockmap[q][y & 3][x & 3])
					return true;
			}
		}
	return false;
}

bool MapCollision(Point pos, Size sz)
{
	return MapCollision(Rect(pos - sz / 2, sz));
}

int kind = 1;

struct JetStory : TopWindow {
	Point pos = Point(0, 0);

	virtual void Paint(Draw& w);

	virtual bool Key(dword key, int count)
	{
		switch(key) {
		case '1':
		case K_1:
			kind = 1;
			break;
		case '2':
		case K_2:
			kind = 2;
			break;
		case K_Y:
		#ifdef PLATFORM_POSIX
		case 'y':
		case 'Y':
		#endif
			left = true;
			break;
		case K_Y|K_KEYUP:
			left = false;
			break;
		case K_U:
		#ifdef PLATFORM_POSIX
		case 'u':
		case 'U':
		#endif
			right = true;
			break;
		case K_U|K_KEYUP:
			right = false;
			break;
		case K_I:
		#ifdef PLATFORM_POSIX
		case 'i':
		case 'I':
		#endif
			down = true;
			break;
		case K_I|K_KEYUP:
			down = false;
			break;
		case K_O:
		#ifdef PLATFORM_POSIX
		case 'o':
		case 'O':
		#endif
			up = true;
			break;
		case K_O|K_KEYUP:
			up = false;
			break;
		case K_P:
		#ifdef PLATFORM_POSIX
		case 'p':
		case 'P':
		case K_SPACE:
		#endif
			fire = true;
			break;
		case K_P|K_KEYUP:
			fire = false;
			break;
		case K_ESCAPE:
			Break();
			break;
		}
		return true;
	}

	void Do();

	JetStory() {
		FullScreen();
		Do();
	//	SetRect(0, 0, 100, 100);
	}
};

bool DoMove(Pointf& pos, double dx, double dy, Size isz)
{
	Pointf p2 = pos;
	p2.x += dx;
	p2.y += dy;
	
	if(MapCollision(p2, isz)) {
		double l = 0;
		double h = 1;
		for(int i = 0; i < 10 && abs(h - l) > 0.01; i++) {
			double p = (h + l) / 2;
	
			Pointf p2 = pos;
			p2.x += p * dx;
			p2.y += p * dy;
			
			if(MapCollision(p2, isz))
				h = p;
			else
				l = p;
		}
		pos.x += l * dx;
		pos.y += l * dy;
		return true;
	}
	pos = p2;
	return false;
}

struct Object {
	Pointf pos;
	Pointf speed = Pointf(0, 0);
	
	bool Move(Size sz, Pointf bounce, Pointf friction, double gravity = 0.01);
	bool Move(Size sz, double bounce, double friction = 0.997, double gravity = 0.01);
};

bool Object::Move(Size sz, Pointf bounce, Pointf friction, double gravity)
{
	speed.y += gravity;

	bool r = false;
	if(DoMove(pos, speed.x, 0, sz)) {
		speed.x *= -bounce.x;
		speed.y *= friction.y;
		r = true;
	}
	if(DoMove(pos, 0, speed.y, sz)) {
		speed.y *= -bounce.y;
		speed.x *= friction.x;
		r = true;
	}
	return r;
}

bool Object::Move(Size sz, double bounce, double friction, double gravity)
{
	return Move(sz, Pointf(bounce, bounce), Pointf(friction, friction), gravity);
}


struct Ship : Object {
	bool left;
};

Ship ship;

struct Missile : Object {
	int kind;
	double accelx;
	
	Missile() { kind = 0; accelx = 0; }
};

Array<Missile> missile;

struct Enemy : Object {
	Image image;

	virtual void Do();
	virtual ~Enemy() {}

};

void Enemy::Do()
{
	Move(image.GetSize(), 0.4);
}

struct ExplosionImage {
	Pointf pos;
	int    start;
};

Array<ExplosionImage> explosion;

struct Debris : Object {
	Size   sz;
	int    start;
	int    end;
};

Array<Debris> debris;

Array<Enemy> enemy;

int flash;

struct Ball : Enemy {
	void SpeedX() {
		speed.x = (Random(2) ? -1 : 1) * Randomf() * 1;
	}
	
	virtual void Do() {
		Move(image.GetSize(), 0.9);
		if(abs(speed.x) + abs(speed.y) < 0.1) {
			speed.y = -Randomf() * 2;
			SpeedX();
		}
	}
	
	Ball() { image = JetStoryImg::ball(); speed.y = 0; SpeedX(); }
};

void GenerateEnemy()
{
	while(enemy.GetCount() < 100) {
		Point pos(Random(MAPX * BLOCKSIZE), (2 * Randomf() - 1) * MAPY * BLOCKSIZE);
		if(!MapCollision(pos, Size(16, 16))) {
			Ball& b = enemy.Create<Ball>();
			b.pos = pos;
		}
	}
}

void Explosion(Pointf pos, int n, double spread)
{
	int ms = msecs();

	for(int i = 0; i <= n / 10; i++) {
		ExplosionImage& m = explosion.Add();
		m.start = ms + Random(n);
		m.pos = pos + Sizef(Randomf() * spread - spread / 2, Randomf() * spread - spread / 2);
	}
	
	n = n / 2 + Random(n / 2);
	for(int i = 0; i < n; i++) {
		Debris& d = debris.Add();
		d.pos = pos;
		d.speed = Pointf(Randomf() * 10 - 5, Randomf() * 10 - 5);
		d.sz = Size(1 + Random(2), 1 + Random(2));
		d.start = ms;
		d.end = ms + 300 + Random(100);
	}
}

void Fragment(const Missile& m)
{
	int n = 50 + Random(50);
	for(int i = 0; i < n; i++) {
		Missile& mm = missile.Add();
		mm.kind = 9;
		mm.pos = m.pos;
		mm.speed = Pointf(Randomf() * 10 - 5, Randomf() * 10 - 5);
	}
}

void JetStory::Do()
{
	static int time = msecs() / 10;

	int ms = msecs();
	
	int m = ms / 10;
	
	int n = m - time;
	time = m;
	
	Size isz = JetStoryImg::ship().GetSize();

	while(n-- > 0) {
		if(left) {
			ship.speed.x -= 0.01;
			ship.left = true;
		}
		else
		if(right) {
			ship.speed.x += 0.01;
			ship.left = false;
		}
		if(up)
			ship.speed.y -= 0.02;

		ship.Move(isz, 0.4, 0.997);
		
		if(fire) {
			static int lastfire = msecs();
			if(ms - lastfire > 60) {
				lastfire = ms;
				Missile& m = missile.Add();
				m.kind = 0;
				m.pos = ship.pos;
				m.speed.y = ship.speed.y - 0.05;
				m.speed.x = ship.speed.x + (ship.left ? -1 : 1) * 5;
			}
		}
		
		if(down) {
			down = false;
			Missile& m = missile.Add();
			m.kind = kind;
			m.pos = ship.pos;
			m.pos.y += 10;
			m.speed = ship.speed;
			if(kind == 1)
				m.accelx = ship.left ? -0.05 : 0.05;
			if(kind == 2)
				m.speed.y += 0.5;
		}
		
		Vector<int> done;
		Size msz = JetStoryImg::fire().GetSize();
		Size msz1 = JetStoryImg::hmissile0().GetSize();
		Size msz2 = JetStoryImg::bomb().GetSize();
		for(int i = 0; i < missile.GetCount(); i++) {
			Missile& m = missile[i];
			m.speed.x += m.accelx;
			if(m.Move(decode(m.kind, 1, msz1, 2, msz2, msz), 0, 1, m.kind ? 0.01 : 0.001)) {
				if(m.kind == 2) {
					Fragment(m);
				}
				if(m.kind != 9)
					Explosion(m.pos, m.kind == 1 ? 100 : 5, m.kind == 1 ? 20 : 4);
				done.Add(i);
			}
			else
			if(m.kind == 9 && Random(8) == 0)
				done.Add(i);
#if 0
			if(m.kind == 1) {
				Debris& d = debris.Add();
				d.pos = m.pos;
				d.speed = m.speed;
				d.speed.x -= sgn(m.speed);
				d.speed.y += 0.2 * (Randomf() - 0.5);
				d.sz = Size(2, 2);
				d.start = ms;
				d.end = ms + 500;
			}
#endif
		}
		missile.Remove(done);
		
		done.Clear();
		for(int i = 0; i < debris.GetCount(); i++) {
			Debris& d = debris[i];
			if(ms > d.end)
				done.Add(i);
			else
				d.Move(d.sz, 0.4);
		}
		debris.Remove(done);
		
		done.Clear();
		for(int i = 0; i < enemy.GetCount(); i++) {
			Enemy& e = enemy[i];
			e.Do();
			Sizef esz = e.image.GetSize();
			Rectf r(e.pos - esz / 2, esz);
			for(int j = 0; j < missile.GetCount(); j++)
				if(r.Contains(missile[j].pos)) {
					done.Add(i);
					Explosion(e.pos, (int)(esz.cx * esz.cy), min(esz.cx, esz.cy));
					if(missile[j].kind == 2)
						Fragment(missile[j]);
					missile.Remove(j);
					break;
				}
		}
		enemy.Remove(done);
	}

	Refresh();
}

void JetStory::Paint(Draw& w)
{
	int ms = msecs();

	Size sz = GetSize();

	bool doflash = flash - ms > 0 && flash - ms < 100000;
	
	w.DrawRect(GetSize(), doflash ? White() : Black());
	
	Size isz = JetStoryImg::ship().GetSize();

	Point topleft = (Point)ship.pos - sz / 2;

	if(!doflash) {
		RTIMING("back3");
		Image m = BlocksImg::back3();
		Size isz = m.GetSize();
		for(int x = 0; x < MAPX * BLOCKSIZE; x += isz.cx)
			for(int y = 0; y < MAPY * BLOCKSIZE; y += isz.cy) {
				Point p = Point(x, y) - topleft;
				if(p.x + sz.cx >= 0 && p.y + sz.cy >= 0 && p.x < sz.cx && p.y < sz.cy)
					w.DrawImage(p.x, p.y, BlocksImg::back3());
			}
	}

	if(!doflash && 0)
		for(int x = 0; x < MAPX; x++)
			for(int y = 0; y < MAPY; y++) {
				Point p = BLOCKSIZE * Size(x, y) - topleft;
				if(p.x + BLOCKSIZE >= 0 && p.y + BLOCKSIZE >= 0 && p.x < sz.cx && p.y < sz.cy)
					w.DrawImage(p.x, p.y, BlocksImg::B0());
			}
	
	static Vector<int> stars;
	static Vector<Color> star_color;
	auto StarColor = []() -> Color {
		const int l = 138;
		const int r = 117;
		return Color(Random(r) + l, Random(r) + l, Random(r) + l);
	};
	ONCELOCK {
		SeedRandom(0);
		for(int i = 0; i < MAPX * BLOCKSIZE; i++) {
			stars.Add(Random(MAPX * BLOCKSIZE));
			star_color.Add(StarColor());
		}
		SeedRandom();
	};
	for(int i = topleft.y; i < 0; i++) {
		if(i - topleft.y > sz.cy)
			break;
		int ii = (0 - i) % stars.GetCount();
		int x = (stars[ii] - topleft.x + 0x70000000) % (MAPX * BLOCKSIZE);
		if(x >= 0 && x < sz.cx)
			w.DrawRect(x, i - topleft.y, 1, 1, star_color[ii]);
		if(Random(10) == 0)
			star_color[ii] = StarColor();
	}
	
	Point sp = sz / 2 - isz / 2;

	int ani3 = (0x7fffffff & ms) / 20 % 3;
	for(auto& m : missile) {
		Image img = decode(m.kind, 1, JetStoryImg::Get((m.speed.x < 0 ? JetStoryImg::I_lhmissile0 : JetStoryImg::I_hmissile0) + ani3),
		                           2, JetStoryImg::bomb(),
		                           9, JetStoryImg::fragment(),
		                           m.speed.x < 0 ? JetStoryImg::erif() : JetStoryImg::fire());
		                           
		Size msz = img.GetSize();
		Point p = (Point)m.pos - topleft - msz / 2;
		w.DrawImage(p.x, p.y, img);
	}

	w.DrawImage(sp.x, sp.y,
	            ship.left ? JetStoryImg::pish() : JetStoryImg::ship());

	int anim = msecs() / 20;
	if(left && (anim & 1))
		w.DrawImage(sp.x + 32, sp.y, anim & 2 ? JetStoryImg::pishb2() : JetStoryImg::pishb());

	if(right && (anim & 1))
		w.DrawImage(sp.x - 32, sp.y, anim & 2 ? JetStoryImg::shipb2() : JetStoryImg::shipb());

	if(up && (anim & 1))
		w.DrawImage(sp.x, sp.y + 16, anim & 2 ? left ? JetStoryImg::pishu() : JetStoryImg::shipu()
		                                      : left ? JetStoryImg::pishu2() : JetStoryImg::shipu2());
	
	for(auto& m : enemy) {
		Size msz = m.image.GetSize();
		Point p = (Point)m.pos - topleft - m.image.GetSize() / 2;
		if(Rect(p, msz).Intersects(sz))
			w.DrawImage(p.x, p.y, m.image);
	}

	for(int i = explosion.GetCount() - 1; i >= 0; i--) {
		ExplosionImage& m = explosion[i];
		Size msz = JetStoryImg::boom1().GetSize();
		int ani = (ms - m.start) / 40;
		if(ani > 4)
			explosion.Remove(i);
		else
		if(ani >= 0) {
			Point p = (Point)m.pos - topleft - msz / 2;
			w.DrawImage(p.x, p.y, JetStoryImg::Get(JetStoryImg::I_boom1 + ani));
		}
	}

	for(auto& m : debris) {
		Point p = (Point)m.pos - topleft;
		w.DrawRect(p.x, p.y, m.sz.cx, m.sz.cy, Blend(LtYellow(), Red(), (ms - m.start) * 255 / (m.end - m.start)));
	}

	for(int x = 0; x < MAPX; x++)
		for(int y = 0; y < MAPY; y++) {
			Point p = BLOCKSIZE * Size(x, y) - topleft;
			if(p.x + BLOCKSIZE >= 0 && p.y + BLOCKSIZE >= 0 && p.x < sz.cx && p.y < sz.cy && jetstory[y][x])
				w.DrawImage(p.x, p.y, BlocksImg::Get(jetstory[y][x]));
		}
	
	int x = MAPX;
	
	while(x * BLOCKSIZE - topleft.x < sz.cx) {
		for(int y = 0; y < MAPY; y++) {
			Point p = BLOCKSIZE * Size(x, y) - topleft;
			if(p.x + BLOCKSIZE >= 0 && p.y + BLOCKSIZE >= 0 && p.x < sz.cx && p.y < sz.cy)
				w.DrawImage(p.x, p.y, BlocksImg::Get(jetstory[y][MAPX - 1]));
		}
		x++;
	}
	
	x = -1;
	while(x * BLOCKSIZE - topleft.x + BLOCKSIZE >= 0) {
		for(int y = 0; y < MAPY; y++) {
			Point p = BLOCKSIZE * Size(x, y) - topleft;
			if(p.x + BLOCKSIZE >= 0 && p.y + BLOCKSIZE >= 0 && p.x < sz.cx && p.y < sz.cy)
				w.DrawImage(p.x, p.y, BlocksImg::Get(jetstory[y][0]));
		}
		x--;
	}
	
	static BiVector<int> fpsq;

	fpsq.AddTail(ms);
	while(fpsq.GetCount() > 20)
		fpsq.DropHead();
	
	double fps = 0;
	if(fpsq.GetCount())
		fps = 1000.0 / ((fpsq.Tail() - fpsq.Head()) / fpsq.GetCount());

	w.DrawRect(0, 0, sz.cx, 24, Gray());
	w.DrawText(0, 0, Format("X:%5.2f Y:%5.2f enemy:%5d missiles:%5d debris:%5d FPS:%3.2f",
	           ship.pos.x, ship.pos.y, enemy.GetCount(), missile.GetCount(), debris.GetCount(), fps),
	           Monospace(20), White());
	
	PostCallback([=] { Do(); });
}


GUI_APP_MAIN
{
//	ImportMap();

//	InitSound();

	
	BlockMap();

	for(int i = 0; i < 30; i++)
		BlocksImg::Set(i, Upscale2x(BlocksImg::Get(i)));

	GenerateEnemy();

	ship.pos.x = 4000;
	ship.pos.y = -80;
	
	JetStory js;
	js.Run();
}
