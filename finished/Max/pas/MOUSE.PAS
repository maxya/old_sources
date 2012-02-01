unit mouse;

  interface
    uses dos;
    type array32word = array[0..31] of word;
    const
      hand : array32word = ($ffff,$ffff,$ffff,$ffff,$ffff,$ffff,$ffff,$ffff,
                            $ffff,$ffff,$ffff,$ffff,$ffff,$ffff,$ffff,$ffff,
                            $0000,$0000,$0700,$0500,$0500,$05FC,$0554,$0D54,
                            $1554,$1004,$0804,$0404,$0208,$0208,$0208,$0208);
    var  mouse_clicked_x,
         mouse_clicked_y  : word;

    function  mouse_area   (var xma)        : word;
    function  mouse_clicked(button:word)    : boolean;
    function  mousex           : word;
    function  mousey           : word;
    function  mousebutton      : word;
    function  mouse_swreset    : boolean;
    procedure get_sensitivity         ( var x           : word;
                                        var y           : word;
                                        var speed       : word        );
    procedure set_sensitivity         (     x           : word;
                                            y           : word;
                                            speed       : word        );
    procedure physical_movement       ( var x           : integer;
                                        var y           : integer     );
    procedure set_ratio               (     x,y         : word        );
    procedure cond_off                (     ux,uy,lx,ly : word        );
    procedure set_speed2              (     threshold   : word        );
    procedure mouse_cursor            (     onoff       : boolean     );
    procedure mouse_position          ( var button_stat : word;
                                        var x           : word;
                                        var y           : word        );
    procedure set_mouse_position      (     x,y         : word        );
    procedure set_mouse_x_bounds      (     xl,xu       : word        );
    procedure set_mouse_y_bounds      (     yl,yu       : word        );
    procedure set_mouse_cursor        (     x,y         : word;
                                        var point       : array32word );
    procedure set_text_cursor         (     aorh,
                                            startof,
                                            endof       : word        );
    function  mouseparams             ( var num_buttons : word        ):boolean;

    function  button_pressed          (     button      : word;
                                        var count       : word;
                                        var x           : word;
                                        var y           : word        ):boolean;
    function  button_released         (     button      : word;
                                        var count       : word;
                                        var x           : word;
                                        var y           : word        ):boolean;


  implementation

  function mouse_area;
  var x:integer;
      mx,my,button : word;
      ma : array[1..100,1..4] of word absolute xma;
  begin
    x:=1;
    mouse_position(button,mx,my);
    while ma[x,1]<>0 do begin
      if     (mx>=ma[x,1])
         and (mx<=ma[x,2])
         and (my>=ma[x,3])
         and (my<=ma[x,4]) then begin
        mouse_area:=x;
        exit
        end;
      x:=x+1
      end;
    mouse_area:=0
    end;

    function mouse_swreset;
    var regs:registers;
    begin
      regs.ax:=$21;
      intr($33,regs);
      mouse_swreset:=regs.ax=$ffff
      end;

    procedure get_sensitivity;
    var regs:registers;
    begin
      regs.ax:=$1b;
      intr($33,regs);
      x:=regs.bx;
      y:=regs.cx;
      speed:=regs.dx
      end;

    procedure set_sensitivity;
    var regs:registers;
    begin
      regs.ax:=$1a;
      regs.bx:=x;
      regs.cx:=y;
      regs.dx:=speed;
      intr($33,regs)
      end;

    procedure physical_movement;
    var regs:registers;
    begin
      regs.ax:=$b;
      intr($33,regs);
      x:=regs.cx;
      y:=regs.dx
      end;

    procedure set_ratio;
    var regs:registers;
    begin
      regs.ax:=$0f;
      x:=x and $7fff;
      y:=y and $7fff;
      regs.cx:=x;
      regs.dx:=y;
      intr($33,regs)
      end;

    procedure cond_off;
    var regs:registers;
    begin
      regs.ax:=$10;
      regs.cx:=ux;
      regs.dx:=uy;
      regs.si:=lx;
      regs.di:=ly;
      intr($33,regs)
      end;

    procedure set_speed2;
    var regs: registers;
    begin
      regs.ax:=$13;
      regs.dx:=threshold;
      intr($33,regs)
      end;

    function mouseparams;
    var regs: registers;
    begin
      regs.ax:=$0;
      intr($33,regs);
      mouseparams:=regs.ax=$ffff;
      num_buttons:=regs.bx
      end;

    procedure mouse_cursor;
    var regs: registers;
    begin
      if onoff then regs.ax:=$1 else regs.ax:=$2;
      intr($33,regs)
      end;

    procedure mouse_position;
    var regs: registers;
    begin
      regs.ax:=$3;
      intr($33,regs);
      button_stat:=regs.bx;
      x:=regs.cx;
      y:=regs.dx
      end;

    function mousex;
    var b,x,y : word;
    begin
      mouse_position(b,x,y);
      mousex:=x
      end;

    function mousey;
    var b,x,y : word;
    begin
      mouse_position(b,x,y);
      mousey:=y
      end;

    function mousebutton;
    var b,x,y : word;
    begin
      mouse_position(b,x,y);
      mousebutton:=b
      end;

    procedure set_mouse_position;
    var regs: registers;
    begin
      regs.ax:=$4;
      regs.cx:=x;
      regs.dx:=y;
      intr($33,regs)
      end;

    procedure set_mouse_x_bounds;
    var regs: registers;
    begin
      regs.ax:=$7;
      regs.cx:=xl;
      regs.dx:=xu;
      intr($33,regs)
      end;

    procedure set_mouse_y_bounds;
    var regs: registers;
    begin
      regs.ax:=$8;
      regs.cx:=yl;
      regs.dx:=yu;
      intr($33,regs)
      end;

    function button_pressed;
    var regs:registers;
    begin
      regs.ax:=$5;
      regs.bx:=button;
      intr($33,regs);
      count:=regs.bx;
      x:=regs.cx;
      y:=regs.dx;
      button_pressed:=(regs.ax=1)
      end;

    function mouse_clicked;
    var trash1 : boolean;
        count : word;
    begin
      trash1:=button_pressed(button,count,mouse_clicked_x,mouse_clicked_y);
      mouse_clicked:=count>0
      end;




    function button_released;
    var regs:registers;
    begin
      regs.ax:=$5;
      regs.bx:=button;
      intr($33,regs);
      count:=regs.bx;
      x:=regs.cx;
      y:=regs.dx;
      button_released:=(regs.ax=0)
      end;

    procedure set_mouse_cursor;
    var regs : registers;
    begin
      regs.ax:=$9;
      regs.bx:=x;
      regs.cx:=y;
      regs.es:=seg(point[0]);
      regs.dx:=ofs(point[0]);
      intr($33,regs)
      end;

    procedure set_text_cursor;
    var regs:registers;
    begin
      regs.ax:=$0a;
      regs.bx:=aorh;
      if aorh=0 then begin
        startof:=startof or $00ff;
        endof:=endof and $ff00
        end;
      regs.cx:=startof;
      regs.dx:=endof;
      intr($33,regs)
      end;

    end.