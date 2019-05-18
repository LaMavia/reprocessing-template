module Vector = {
  type t = {
    x: float,
    y: float,
  };
  let create = (~x=0., ~y=0., ()): t => {x, y};
  let add = (a: t, b: t): t => {x: a.x +. b.x, y: a.y +. b.y};
  let mult = (n: float, vec: t): t => {x: vec.x *. n, y: vec.y *. n};
  let div = (n: float, vec: t): t => {x: vec.x /. n, y: vec.y /. n};
  let magSq = (vec: t) => {
    let {x, y} = vec;
    x *. x +. y *. y;
  };
  let mag = (vec: t) => sqrt(magSq(vec));
  let from_angle = (angle, ~length=1., ()): t => {
    x: length *. cos(angle),
    y: length *. sin(angle),
  };
  let heading = (vec: t) => atan2(vec.x, vec.y);
  let limit = (max: float, vec: t): t => {
    let mSq = magSq(vec);
    if (mSq > max *. max) {
      vec |> div(sqrt(mSq)) |> mult(max);
    } else {
      vec;
    };
  };
  let normolize = (vec: t): t => {
    let mag = mag(vec);
    mag == 0. ? vec : div(mag, vec);
  };
  let setMag = (n: float, vec: t): t => vec |> normolize |> mult(n);

  let vecToPoint = (vec: t) => (
    vec.x |> int_of_float,
    vec.y |> int_of_float,
  );
};