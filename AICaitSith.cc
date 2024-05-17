#include "Player.hh"
//#include <list>
//#include <queue>



/**
 * Write the name of your player and save this file
 * with the same name and .cc extension.
 */
#define PLAYER_NAME CaitSith


struct PLAYER_NAME : public Player {

  /**
   * Factory: returns a new instance of this class.
   * Do not modify this function.
   */
  static Player* factory () {
    return new PLAYER_NAME;
  }

  /**
   * Types and attributes for your player can be defined here.
   */
  typedef vector<vector<pair<int, int>>> VP; 
  typedef vector<vector<int>> VI;
  VP dist;
  VI far;
Pos fNear(Pos p){
  //Detecta si hay un hellhound cerca.
    
    queue<Pos> Q;
    vector<vector<bool>>visitados(40, vector<bool>(80,false));
    far = VI(40, vector<int>(80,-1));
    Q.push(p);
    visitados[p.i][p.j] = true;
    far[p.i][p.j] = 0;
    while(not Q.empty()){
      Pos c = Q.front();
      Q.pop();
      for(int x = 0; x<8; ++x){
        Pos c2 = c + Dir(x);
        if(pos_ok(c2)){
          far[c2.i][c2.j] = far[c.i][c.j] +1;
         // cerr << far[c2.i][c2.j] << endl;
          if(cell(c2).id!= -1 and unit(cell(c2).id).type == Furyan and far[c2.i][c2.j] <= 11){
            cerr << "----------------------THERE IS A HELLHOUND NEAR------------------------------" << endl;
            return c2;
          }
          else if(far[c2.i][c2.j] > 11){
            return {-1,-1,-1};
          }
          else if(not visitados[c2.i][c2.j]){
            //cerr << x << ' '<< c2.i <<' '<< c2.j << ' ' << cell(p).id << endl;
              Q.push(c2);
              visitados[c2.i][c2.j] = true;
          }
        }
      }
    }
    return {-1,-1,-1};
}
Pos hhNear(Pos p){
  //Detecta si hay un hellhound cerca.
    
    queue<Pos> Q;
    vector<vector<bool>>visitados(40, vector<bool>(80,false));
    far = VI(40, vector<int>(80,-1));
    Q.push(p);
    visitados[p.i][p.j] = true;
    far[p.i][p.j] = 0;
    while(not Q.empty()){
      Pos c = Q.front();
      Q.pop();
      for(int x = 0; x<8; ++x){
        Pos c2 = c + Dir(x);
        if(pos_ok(c2)){
          far[c2.i][c2.j] = far[c.i][c.j] +1;
          //cerr << far[c2.i][c2.j] << endl;
          if(cell(c2).id!= -1 and unit(cell(c2).id).type == Hellhound and far[c2.i][c2.j] <= 20){
            cerr << "----------------------THERE IS A HELLHOUND NEAR------------------------------" << endl;
            return c2;
          }
          else if(far[c2.i][c2.j] > 20){
            return {-1,-1,-1};
          }
          else if(not visitados[c2.i][c2.j]){
            //cerr << x << ' '<< c2.i <<' '<< c2.j << ' ' << cell(p).id << endl;
              Q.push(c2);
              visitados[c2.i][c2.j] = true;
          }
        }
      }
    }
    return {-1,-1,-1};
}

  void escape_enemy_furyan(int id, Pos enemy){
    
    cerr << "escape!" << endl;
    Pos p = unit(id).pos; //Este soy yo
    if(p.j != enemy.j){
      if(p.j > enemy.j){
        if(enemy.i > p.i){
           if(pos_ok(p+RT) and cell(p+RT).type != Rock)command(id, RT);
           else if(pos_ok(p+Right) and cell(p+Right).type != Rock) command(id, Right);
           else if(pos_ok(p+Top) and cell(p+Top).type != Rock) command(id, Top);
           else if(pos_ok(p+BR) and cell(p+BR).type != Rock) command(id, BR);
           else command(id, TL);
        }
        else if(enemy.i < p.i){
           if(pos_ok(p+BR) and cell(p+BR).type != Rock)command(id, BR);
           else if(pos_ok(p+Right) and cell(p+Right).type != Rock)command(id, Right);
           else if(pos_ok(p+Bottom) and cell(p+Bottom).type != Rock) command(id, Bottom);
           else if(pos_ok(p+LB) and cell(p+LB).type != Rock) command(id, LB);
           else command(id, RT);
        }
        else{
           if(pos_ok(p+Right) and cell(p+Right).type != Rock)command(id, Right);
           else if(pos_ok(p+RT) and cell(p+RT).type != Rock)command(id, RT);
           else if(pos_ok(p+BR) and cell(p+BR).type != Rock) command(id, BR);
           else if(pos_ok(p+Top) and cell(p+Top).type != Rock) command(id, Top);
           else command(id, Bottom);
        }
      }
      else{
        if(enemy.i > p.i){
           if(pos_ok(p+TL) and cell(p+TL).type != Rock)command(id, TL);
           else if(pos_ok(p+Left) and cell(p+Left).type != Rock)command(id, Left);
           else if(pos_ok(p+Top) and cell(p+Top).type != Rock)command(id, Top);
           else if(pos_ok(p+RT) and cell(p+RT).type != Rock) command(id, RT);
           else command(id, LB);
        }
        else if(enemy.i < p.i){
           if(pos_ok(p+LB) and cell(p+LB).type != Rock)command(id,LB);
           else if(pos_ok(p+Left) and cell(p+Left).type != Rock) command(id, Left);
           else if(pos_ok(p+Bottom) and cell(p+Bottom).type != Rock)command(id, Bottom);
           else if(pos_ok(p+BR) and cell(p+BR).type != Rock) command(id, BR);
           else command(id, TL);
        }
        else{
           if(pos_ok(p+Left) and cell(p+Left).type != Rock)command(id, Left);
           else if(pos_ok(p+TL) and cell(p+TL).type != Rock)command(id, TL);
           else if(pos_ok(p+LB) and cell(p+LB).type != Rock)command(id, LB);
           else if(pos_ok(p+Top) and cell(p+Top).type != Rock) command(id, Top);
           else command(id, Bottom);
        }
      }
    }
    else{
        if(enemy.i > p.i){
          if(pos_ok(p+Top) and cell(p+Top).type != Rock)command(id, Top);
          else if(pos_ok(p+TL) and cell(p+TL).type != Rock)command(id, TL);
          else if(pos_ok(p+RT) and cell(p+RT).type != Rock)command(id, RT);
          else if(pos_ok(p+Right) and cell(p+Right).type != Rock) command(id, Right);
          else command(id, Left);
        }
        else{
           if(pos_ok(p+Bottom) and cell(p+Bottom).type != Rock)command(id, Bottom);
           else if(pos_ok(p+BR) and cell(p+BR).type != Rock) command(id, BR);
           else if(pos_ok(p+LB) and cell(p+LB).type != Rock)command(id, LB);
          else if(pos_ok(p+Right) and cell(p+Right).type != Rock) command(id, Right);
          else command(id, Left);
        }
    }
  }
  void escape_enemy_pioneer(int id, Pos h, Pos f){
    
    cerr << "escape!" << endl;
    Pos p = unit(id).pos; //Este soy yo
    //Primero escapar del que tengo más cerca, eso lo primero de todo.

    if(p.j != f.j){
      if(p.j > f.j){
        if(f.i > p.i){

          if(h.i < p.i and h.j > p.j) command(id, Right);
          else command(id, RT);

        } 
        else if(f.i < p.i){
           if(h.i > p.i and h.j > p.j) command(id, Right);
           else command(id, BR);
        }
        else{
           if(h.i == p.i and h.j > p.j) command(id, RT);
           else command(id, Right);
        }
      }
      else{
        if(f.i > p.i){
           if(h.i < p.i and h.j < p.j) command(id, Left);
           else command(id, TL);
        }
        else if(f.i < p.i){
           if(h.i > p.i and h.j < p.j) command(id, Left);
           else command(id,LB);
        }
        else{
           if(h.i == p.i and h.j < p.j) command(id, TL);
           else command(id, Left);
        }
      }
    }
    else{
        if(f.i > p.i){
           if(h.i < p.i and h.j == p.j) command(id, Right);
           else command(id, Top);
        }
        else{
           if(h.i > p.i and h.j == p.j) command(id, Left);
           else command(id, Bottom);
        }
    }
  } 
  void move_towards(int id, Pos destino){
    //Tengo que moverme a la posición más cercana del destino porque pierdo la información
    //para la siguiente ronda.
    Pos p = unit(id).pos; //Posición inicial
    Pos di = destino; //Destino inicial. Al principio es {0,1,0}
    pair<int,int> inicio = make_pair(p.i, p.j);
    //cerr << di.i << " " << di.j << endl;
    while(dist[di.i][di.j] != inicio){
      di = {dist[di.i][di.j].first,dist[di.i][di.j].second, 0};
    }
    int xi = (di.i - p.i);
    int yi = (di.j - p.j);
    if(xi < 0){
        if(yi > 0){
          command(id, RT);
        }
        else if(yi < 0){
          command(id, TL);
        }
        else command(id, Top);
    }
    else if(xi > 0){
        if(yi > 0){
          command(id, BR);
        }
        else if(yi < 0){
          command(id, LB);
        }
        else command(id, Bottom);
    }
    else{
      if(yi > 0){
          command(id, Right);
      }
      else command(id, Left);

    }
    dist.clear();
  }
  Pos bfs_pioneer(Pos p){ //Dada una posición (al principio es la inicial del pionero)

      queue<Pos> Q; //Vecinos.
      vector<vector<bool>>visitados(40, vector<bool>(80,false)); //Vector de visitados.
      dist = VP(40,vector<pair<int,int>>(80, {-1,-1}));
      Q.push(p);
      visitados[p.i][p.j] = true; //Ya he visitado la posición en la que estoy.

      vector<int> perm = random_permutation(8);

      while(not Q.empty()){
        Pos c = Q.front();
        Q.pop();
        if (pos_ok(c)){
          int id2 = cell(c).id;
          if(id2 == -1 and cell(c).owner != me()){ //Si no hay nadie y la casilla no es mía.
            if(cell(c).type == Cave) return c; //Si no tiene una piedra me muevo.
          }
          for(int x = 0; x < 8; ++x){ //Ahora miro todos los vecinos de la posición.
            Pos c2 = c + Dir(perm[x]);
            id2 = cell(c2).id;
            if(pos_ok(c2) and not visitados[c2.i][c2.j] and cell(c2).type != Rock){
                Q.push(c2);
                visitados[c2.i][c2.j] = true;
                dist[c2.i][c2.j] = {c.i, c.j}; //En la posición nueva meto en la que estaba antes.
                
            }
          }
        }
      }
      return {-1,-1,-1};
  }
  Pos bfs_furyan(Pos p){ //Dada una posición (al principio es la inicial del pionero)

      queue<Pos> Q; //Vecinos.
      vector<vector<bool>>visitados(40, vector<bool>(80,false)); //Vector de visitados.
      dist = VP(40,vector<pair<int,int>>(80, {-1,-1}));

      Q.push(p);
      visitados[p.i][p.j] = true; //Ya he visitado la posición en la que estoy.
      vector<int> perm = random_permutation(8);

      while(not Q.empty()){
        Pos c = Q.front();
        Q.pop();
        if(pos_ok(c) and cell(c).id != -1 and unit(cell(c).id).player != me() and unit(cell(c).id).type != Hellhound){ //Hay alguien
          cerr <<"Enemy target acquired!" << endl;
          return c; //Si no es ni hellhound ni mío
        }
        for(int x = 0; x < 8; ++x){ //Ahora miro todos los vecinos de la posición.
          Pos c2 = c + Dir(perm[x]);
          if(pos_ok(c2) and not visitados[c2.i][c2.j] and cell(c2).type != Rock){
              Q.push(c2);
              visitados[c2.i][c2.j] = true;
              dist[c2.i][c2.j] = {c.i, c.j}; //En la posición nueva meto en la que estaba antes.
              
          }
        }
      }
      return {-1,-1,-1};
  }

  void move_furyans(){
    vector<int> F = furyans(me());
    for(int id : F){
      Pos p = unit(id).pos; 
      Pos hh = hhNear(p);    
      if(hh.i == -1){ //No hay hellhound a rango <= 4 así que me puedo mover libremente.
        Pos destino = bfs_furyan(p);
        move_towards(id, destino);
      }
      else{
        escape_enemy_furyan(id, hh);
      }
    }
  }

  void move_pioneers(){
    vector<int> P = pioneers(me());
    for(int id : P){
      Pos p = unit(id).pos; //Posición inicial del pionero.  
      Pos hh = hhNear(p);
      Pos f = fNear(p);
      if(hh.i == -1 and f.i == -1){ //No hay hellhound ni furyan cerca así que me puedo mover libremente
         Pos destino = bfs_pioneer(p); //Destino al que me quiero mover será la posición buscada por el BFS.
        move_towards(id, destino);
      } 
      else{
        cerr << "me voy a mover-----------------------------------------------------------" << endl;
        if(hh.i == -1) escape_enemy_furyan(id, f);
        else if(f.i == -1) escape_enemy_furyan(id, hh);
        else escape_enemy_pioneer(id, hh, f);
      }
    }
  }

  /**
   * Play method, invoked once per each round.
   */
  virtual void play () {
        move_pioneers();
        move_furyans();
  }

};


/**
 * Do not modify the following line.
 */
RegisterPlayer(PLAYER_NAME);
