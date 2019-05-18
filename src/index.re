open Reprocessing;
open Vector;

/** Width of the screen */
let width = 1440;

/** Height of the screen */
let height = 900;

let dt = 1. /. 60.;

type particleT = {
  vel: Vector.t,
  pos: Vector.t,
  size: float,
};

type stateT = {
  showGrid: bool,
  showColors: bool,
  particles: array(particleT),
};

let initParticles = (~n: int, ~size: float): array(particleT) => {
  let m = n * n;
  let sx = width / n;
  let sy = width / n;
  let arr =
    Array.init(
      m,
      i => {
        let x = i mod n - n / 2;
        let y = i / n - n / 2;
        {
          vel: Vector.create(~x=0.0, ~y=0.0, ()),
          pos:
            Vector.create(
              ~x=x * sx |> float_of_int,
              ~y=y * sy |> float_of_int,
              (),
            ),
          size,
        };
      },
    );
  arr;
};

let foo = ({x, y}: Vector.t): Vector.t => {
  x: x*.y,
  y: x*.y,
};

let applyForce = (f: Vector.t, dt: float, p: particleT): particleT => {
  ...p,
  vel: f |> Vector.mult(dt) |> Vector.add(p.vel),
};

let applyVel = (dt: float, p: particleT): particleT => {
  ...p,
  pos: p.vel |> Vector.mult(dt) |> Vector.add(p.pos),
};

let setup = env => {
  Env.size(~width, ~height, env);
  Draw.background(Constants.white, env);
  let particles = initParticles(~n=90, ~size=2.);
  {particles, showGrid: false, showColors: false};
};

let draw = (state: stateT, env) => {
  Draw.pushMatrix(env);
  Draw.translate(
    ~x=width / 2 |> float_of_int,
    ~y=height / 2 |> float_of_int,
    env,
  );
  // Draw.background(Constants.white, env);
  let dt = 1./.(float_of_int(Env.frameRate(env))*.1.);
  {
    ...state,
    particles:
      state.particles
      |> Array.map((p: particleT) => {
           let f = p.pos |> foo;
           let particle =
             p
             |> applyForce(f, dt)
             |> applyVel(dt);
           let center = p.pos |> Vector.vecToPoint;
           Draw.fill({
             r: 0.,
             g: 0.,
             b: 0.,
             a: 0.1
           }, env);
           Draw.ellipse(
             ~center,
             ~radx=particle.size |> int_of_float,
             ~rady=particle.size |> int_of_float,
             env,
           );
           particle;
         }),
  };
};

run(~setup, ~draw, ());