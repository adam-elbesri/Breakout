#include <Grapic.h>
#include <iostream>
using namespace std;
using namespace grapic;
const int DIMW = 500;
const int G=9.8;
const int NMAX=40;

struct brique
{
    int x0;
    float y0;
    int xmax;
    int ymax;
};

struct Mur_De_Briques
{
    brique Tab[NMAX];
    int nb_briques=0;
};

void initialisation(Mur_De_Briques &mdb)
{
    int x=0;
    float y=480;
    int xma=60;
    int yma=500;

    for ( int i=0;i<8; i++ )
    {
        mdb.Tab[i].x0=x;
        mdb.Tab[i].xmax=xma;
        mdb.Tab[i].y0=y;
        mdb.Tab[i].ymax=yma;
        x=xma+03;
        xma=xma+63;

    }
    yma=yma-23;
    y=y-23;
    x=0;
    xma=60;
     for ( int j=8;j<16; j++ )
    {
        mdb.Tab[j].x0=x;
        mdb.Tab[j].xmax=xma;
        mdb.Tab[j].y0=y;
        mdb.Tab[j].ymax=yma;
        x=xma+03;
        xma=xma+63;

    }
    yma=yma-23;
    y=y-23;
    x=0;
    xma=60;
     for ( int f=16;f<24; f++ )
    {
        mdb.Tab[f].x0=x;
        mdb.Tab[f].xmax=xma;
        mdb.Tab[f].y0=y;
        mdb.Tab[f].ymax=yma;
        x=xma+03;
        xma=xma+63;

    }
    yma=yma-23;
    y=y-23;

    x=0;
    xma=60;
     for ( int t=24;t<32; t++ )
    {
        mdb.Tab[t].x0=x;
        mdb.Tab[t].xmax=xma;
        mdb.Tab[t].y0=y;
        mdb.Tab[t].ymax=yma;
        x=xma+03;
        xma=xma+63;

    }
    yma=yma-23;
    y=y-23;

    x=0;
    xma=60;
     for ( int a=32;a<40; a++ )
    {
        mdb.Tab[a].x0=x;
        mdb.Tab[a].xmax=xma;
        mdb.Tab[a].y0=y;
        mdb.Tab[a].ymax=yma;
        x=xma+03;
        xma=xma+63;

    }
}
void deplacement (int &mi,int &ma) // déplacement du joueur
    {


        if (isKeyPressed(SDLK_LEFT))
        {
            if ( mi >0)
            {
                mi=mi-1;
                ma=ma-1;
            }
        }
        if (isKeyPressed(SDLK_RIGHT))
        {
           if(ma <500)
           {
                mi=mi+1;
                ma=ma+1;
           }
        }
    }
struct Vec2
{
	float x, y;
};

struct Particle
{
	Vec2 p;
	Vec2 v;
	Vec2 f;
	float m;
	Image texture=image("data/bat_blue.png");
	Image background=image("data/space.jpg");
	Image ball=image("data/ball_yellow.png");

};

 void draw_MurDeBriques(Mur_De_Briques &mdb)        // Dessine les briques
 {
     for (int i=0;i<40;i++)
     {
         color(0, 153, 204);
         rectangleFill(mdb.Tab[i].x0,mdb.Tab[i].y0,mdb.Tab[i].xmax,mdb.Tab[i].ymax);
     }
 }

void draw_module(int &mi, int &ma, Particle &p)
{

    rectangleFill(mi,0,ma,5);
    color(255, 0, 0);
    image_draw(p.texture,(mi-10),-20,((ma-mi)+15),40);

}
Vec2 make_vec2(float x, float y)
{
    Vec2 v;
    v.x = x;
    v.y = y;
    return v;
}

Vec2 operator+(const Vec2& a, const Vec2& b)
{
	Vec2 r;
	r.x = a.x + b.x;
	r.y = a.y + b.y;
	return r;
}

Vec2 operator-(const Vec2& a, const Vec2& b)
{
	Vec2 r;
	r.x = a.x - b.x;
	r.y = a.y - b.y;
	return r;
}

Vec2 operator+=(Vec2& a, const Vec2& b)
{
	a.x += b.x;
	a.y += b.y;
	return a;
}

Vec2 operator*(float a, const Vec2& b)
{
	Vec2 r;
	r.x = a * b.x;
	r.y = a * b.y;
	return r;
}

void updateParticle(Particle& part)
{
    const float dt = 0.007;
    if (part.m>0)
    {
        part.v = part.v + (dt/part.m)*part.f;
        part.p = part.p + dt*part.v;
        part.f.x = 0;
        part.f.y = 0;
    }
}
void collision(Mur_De_Briques &mdb,Particle& part, int &ma, int &mi)
{
	int diff=(mi+((ma-mi)/2));
	for (int i=0; i<40; i++)
	{
	    if ((part.p.x <= diff && part.p.x >=mi-10) && (part.p.y <= 0)) // collision module coté gauche ( même trajectoire )
		{
			part.p.x = -part.p.x;
			part.p.y = -part.p.y;
			part.v.y = -part.v.y;
		}
		if ((part.p.x <= ma+5 && part.p.x >diff) && (part.p.y <=0))    // collision module coté droit ( trajectoire mirroir )
		{
			part.p.y = 5 - (part.p.y - 5);
			part.v.y = -part.v.y;
		}
        if (part.p.x < 0)                                              // collision mur gauche
		{
			part.p.x = -part.p.x;
			part.v.x = -part.v.x;
		}

		if (part.p.x >= DIMW)                                          //colission mur droit
		{
			part.p.x = DIMW-(part.p.x-DIMW);
			part.v.x = -part.v.x;
		}

		if (part.p.y >= DIMW)                                           // collision plafond
		{
			part.p.y = DIMW - (part.p.y - DIMW);
			part.v.y = -part.v.y;
		}
		if ((part.p.x <= mdb.Tab[i].xmax-1 && part.p.x >=mdb.Tab[i].x0+1) && (part.p.y > mdb.Tab[i].y0 && part.p.y< mdb.Tab[i].y0+1 ))  // collision brique en bas
		{
			part.p.y = mdb.Tab[i].y0 - (part.p.y - mdb.Tab[i].y0);
			part.v.y = -part.v.y;
			mdb.Tab[i].x0=0;
			mdb.Tab[i].xmax=0;
			mdb.Tab[i].y0=0;
			mdb.Tab[i].ymax=0;
			mdb.nb_briques++;
		}
		if ((part.p.x <= mdb.Tab[i].xmax-1 && part.p.x >=mdb.Tab[i].x0) && (part.p.y > mdb.Tab[i].ymax-1 && part.p.y< mdb.Tab[i].ymax ))     //collision brique en haut
		{
			part.p.y = mdb.Tab[i].ymax - (part.p.y - mdb.Tab[i].ymax);
			part.v.y = -part.v.y;
			mdb.Tab[i].x0=0;
			mdb.Tab[i].xmax=0;
			mdb.Tab[i].y0=0;
			mdb.Tab[i].ymax=0;
			mdb.nb_briques++;
		}
		if ((part.p.x <= mdb.Tab[i].xmax && part.p.x >mdb.Tab[i].xmax-1) && (part.p.y >= mdb.Tab[i].y0 && part.p.y<= mdb.Tab[i].ymax ))  //collision brique cote droit
		{
			part.p.x = (mdb.Tab[i].xmax)-(part.p.x-(mdb.Tab[i].xmax));
			part.v.x = -part.v.x;
			mdb.Tab[i].x0=0;
			mdb.Tab[i].xmax=0;
			mdb.Tab[i].y0=0;
			mdb.Tab[i].ymax=0;
			mdb.nb_briques++;
		}
if ((part.p.x < mdb.Tab[i].x0+1 && part.p.x >=mdb.Tab[i].x0) && (part.p.y >= mdb.Tab[i].y0 && part.p.y<= mdb.Tab[i].ymax ))  //collision brique cote gauche
		{
			part.p.x = (mdb.Tab[i].x0)-(part.p.x-(mdb.Tab[i].x0));
			part.v.x = -part.v.x;
			mdb.Tab[i].x0=0;
			mdb.Tab[i].xmax=0;
			mdb.Tab[i].y0=0;
			mdb.Tab[i].ymax=0;
			mdb.nb_briques++;
		}
	}
}

void computeParticleForceGravityEarth(Particle& part)
{
    part.f = part.f + make_vec2(0, -part.m * G);
}

void initOnEarth(Particle& part)
{
		part.m = 1.0;      // 1kg
		part.p.x = frand(DIMW/2-20, DIMW/2+20 );
		part.p.y = frand(DIMW/2-10, DIMW/2+10 );

		part.v.x = frand(-80.f, 80.f);
		part.v.y = frand(-4.f, 80.f);
}

void updateOnearth(Mur_De_Briques &mdb,Particle& part, int &ma, int &mi)
{
    computeParticleForceGravityEarth(part);
    updateParticle(part);
    collision(mdb,part,  ma,  mi);
}

void drawOnEarth(Particle& part)  // dessine la balle
{
	color( 255, 0, 0 );
    circleFill( part.p.x, part.p.y, 2);
    image_draw(part.ball,part.p.x-5, part.p.y-10,20,20);


}
void draw_particule ( Mur_De_Briques &mdb,Particle &part, int &ma, int &mi)
{
            drawOnEarth(part);
            updateParticle(part);
            updateOnearth(mdb,part, ma, mi);
            collision(mdb,part, ma, mi);
}

int main(int , char** )
{

    bool stop=false;
    int mi = 300;
    int ma=380;


    winInit("Breakout", DIMW, DIMW);

    setKeyRepeatMode(true);
    Mur_De_Briques mdb;
    Particle part;
    brique br;
    initialisation(mdb);
	initOnEarth(part);
	cout<<endl;
	cout<<"  !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"<<endl<<endl;
    cout<<"     UTILISEZ LES FLECHES GAUCHE DROITE POUR DEPLACER LE MODULE DU BAS "<<endl<<endl;
    cout<<"  !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"<<endl<<endl;
    cout<<"  !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"<<endl<<endl;
    cout<<"     APPUYEZ SUR T POUR QUITTER A TOUT MOMENT  "<<endl<<endl;
    cout<<"  !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"<<endl<<endl;
    while( !stop )
    {
        winClear();
                    while (mdb.nb_briques<40 && part.p.y>0)
                        {
                            winClear();
                            image_draw(part.background,0,0);
                            deplacement(mi, ma);
                            draw_particule(mdb,part, ma, mi);
                            draw_module(mi, ma, part);
                            draw_MurDeBriques(mdb);
                            delay(2);
                            print(170,250," SCORE :");
                            print(250,250,mdb.nb_briques);
                             if(isKeyPressed('t'))
                                winQuit();
                            stop = winDisplay();
                        }
                    if( mdb.nb_briques>=40)
                    {
                        image_draw(part.background,0,0);
                        draw_module(mi, ma, part);
                        drawOnEarth(part);
                        draw_MurDeBriques(mdb);
                        print( 1*100, 1*300, "CONGRATULATIONS YOU WIN !");
                        print( 1*150, 1*100, " PRESS T TO QUIT  ");
                        if(isKeyPressed('t'))
                        winQuit();
                        stop = winDisplay();
                    }
                    else
                    {
                    image_draw(part.background,0,0);
                    draw_MurDeBriques(mdb);
                    draw_module(mi, ma, part);
                    color(255, 0, 0);
                    print( 1*120, 1*300, "GAME OVER ! TRY AGAIN :) ");
                    print( 1*150, 1*100, " PRESS T TO QUIT  ");
                    print(170,170," SCORE :");
                    print(260,170,mdb.nb_briques);
                    if(isKeyPressed('t'))
                        winQuit();
                    stop = winDisplay();
                    }

    }
    winQuit();
    return 0;
}
