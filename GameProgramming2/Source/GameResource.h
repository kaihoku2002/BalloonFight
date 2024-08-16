/*
 * 課題1-1 : ゲームフローを完成させよう
 * 作成者  : 大野雅俊
 * 作成日  : 2020/XX/XX
 */
/**
 * ここで画像ファイルへのパスを宣言する
 */

#define Tex_Title			L"Media/Sprite/ShootingGame_Sprite/Title.png"
#define Tex_Over	    	L"Media/Sprite/ShootingGame_Sprite/GameOver.png"
#define Tex_Clear	    	L"Media/Sprite/ShootingGame_Sprite/GameClear.png"
#define Tex_BackBack		L"Media/Sprite/ShootingGame_Sprite/background_back.png"
#define Tex_BackAnim		L"Media/Sprite/ShootingGame_Sprite/BackAnim.png"
#define Tex_bBacGround			L"Media/Sprite/ShootingGame_Sprite/BBackground.png"
#define Tex_bBackAnim		L"Media/Sprite/ShootingGame_Sprite/BBackAnim.png"

#define Tex_Player   		L"Media/Sprite/ShootingGame_Sprite/Player.png"

//オブジェクト関連
#define Tex_Block   			L"Media/Sprite/ShootingGame_Sprite/block.png"
#define Tex_BlockBer  			L"Media/Sprite/ShootingGame_Sprite/blockbar.png"
#define Tex_LeftBlock  			L"Media/Sprite/ShootingGame_Sprite/leftblock.png"
#define Tex_RightBlock  		L"Media/Sprite/ShootingGame_Sprite/rightblock.png"
#define Tex_Ground  			L"Media/Sprite/ShootingGame_Sprite/ground.png"
#define Tex_LeftGround  		L"Media/Sprite/ShootingGame_Sprite/leftground.png"
#define Tex_RightGround  		L"Media/Sprite/ShootingGame_Sprite/rightground.png"
#define Tex_Cloud  				L"Media/Sprite/ShootingGame_Sprite/cloud.png"
#define Tex_Wave  				L"Media/Sprite/ShootingGame_Sprite/wave.png"
#define Tex_EndWave  			L"Media/Sprite/ShootingGame_Sprite/endwave.png"

//UI
#define Tex_I_UI				L"Media/Sprite/ShootingGame_Sprite/I.png"
#define Tex_Top_UI				L"Media/Sprite/ShootingGame_Sprite/Top.png"
#define Tex_PHASE_UI				L"Media/Sprite/ShootingGame_Sprite/PHASE-.png"
#define Tex_Remain				L"Media/Sprite/ShootingGame_Sprite/remain.png"
#define Tex_Score				L"Media/Sprite/ShootingGame_Sprite/Number.png"
#define Tex_Addscore			L"Media/Sprite/ShootingGame_Sprite/addscore.png"

//敵
#define Tex_Enemy1				L"Media/Sprite/ShootingGame_Sprite/enemy.png"

//bonusステージ関連
#define Tex_BGround  			L"Media/Sprite/ShootingGame_Sprite/BGround.png"
#define Tex_BPipe  				L"Media/Sprite/ShootingGame_Sprite/Pipe.png"
#define Tex_BBalloon       L"Media/Sprite/ShootingGame_Sprite/bounusballoon.png"

//タイトル画面の風景
#define Tex_titleballoon  		L"Media/Sprite/ShootingGame_Sprite/titleballoon.png"

//------------------------------------------------------------------------------
#define Tex_Thunder			L"Media/Sprite/ShootingGame_Sprite/Thunder.png"
#define Tex_ThunderBall		L"Media/Sprite/ShootingGame_Sprite/ThunderBall.png"

#define Tex_Fish			L"Media/Sprite/ShootingGame_Sprite/fish.png"
//-----------------------------------------------------------------------------------------
#define Tex_EnteringWater   L"Media/Sprite/ShootingGame_Sprite/EnteringWater.png"
#define Tex_Bubble			L"Media/Sprite/ShootingGame_Sprite/bubble.png"

#define Tex_Black			L"Media/Sprite/ShootingGame_Sprite/Black.png"
#define Tex_Black           L"Media/Sprite/ShootingGame_Sprite/Black.png"
#define Tex_BounusPerfect   L"Media/Sprite/ShootingGame_Sprite/bounusperfect.png"
#define Tex_PTS             L"Media/Sprite/ShootingGame_Sprite/PTS.png"
#define Tex_Symbol          L"Media/Sprite/ShootingGame_Sprite/symbol.png"

/**
 * ここでサウンドファイルへのパスを宣言する
 * 使用可能な形式は Waveファイル(.wav)
 */

//ゲームスタート
const char* const PhaseStart = "Media/Sounds/BGM/phaseStart.wav";

//エネミー降下
const char* const EnemyDown = "Media/Sounds/BGM/EnemyDown.wav";

//フェ-ズクリア
const char* const PhaseCler = "Media/Sounds/BGM/PhaseCler.wav";

//エネミー死亡時
const char* const EnemyDeath = "Media/Sounds/BGM/EnemyDeath.wav";

//プレイヤージャンプ
const char* const Jump = "Media/Sounds/BGM/Jump.wav";

//プレイヤー歩行
const char* const Step = "Media/Sounds/BGM/Step.wav";

//プレイヤーの復活
const char* const Respawn = "Media/Sounds/BGM/Respawn.wav";

//ぶつかった音
const char* const Hit = "Media/Sounds/BGM/Hit.wav";

//風船が割れた音
const char* const BalloonBom = "Media/Sounds/BGM/BalloonBom.wav";

//エネミーの羽音
const char* const EnemyJump = "Media/Sounds/BGM/EnemyJump.wav";

//泡発生
const char* const Buble = "Media/Sounds/BGM/Buble.wav";

//泡取得
const char* const BubleBoom = "Media/Sounds/BGM/BubleBoom.wav";

//ゲームオーバー
const char* const SGameOver = "Media/Sounds/BGM/GameOver.wav";

//入水
const char* const Water = "Media/Sounds/BGM/Water.wav";

//プレイヤー落下
const char* const Fall = "Media/Sounds/BGM/Fall.wav";

//感電死
const char* const ThunderDeath = "Media/Sounds/BGM/ThunderDeath.wav";

//魚が顔を出したとき
const char* const SFish = "Media/Sounds/BGM/Fish.wav";

//魚死
const char* const SFishDeath = "Media/Sounds/BGM/FishDeath.wav";

//雷出現
const char* const SThunder = "Media/Sounds/BGM/Thunder.wav";

//雷反射
const char* const ThunderHit = "Media/Sounds/BGM/ThunderHit.wav";

//エネミーの着地
const char* const SEnemyLanding = "Media/Sounds/BGM/EnemyLanding.wav";

//ボーナスステージのBGM
const char* const BonusBgm = "Media/Sounds/BGM/BonusBgm.wav";

//ボーナスポイント
const char* const Point = "Media/Sounds/BGM/Point.wav";

//ボーナスパーフェクト
const char* const Perfect = "Media/Sounds/BGM/Perfect.wav";
