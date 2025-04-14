## Window API를 이용해 구현한 2D 게임 엔진
<SceneManager>
  <Scene name="SampleScene">
    <Layer name="Default">
      <GameObject name="Player">
        <Component type="Transform" />
        <Component type="SpriteRenderer" />
        <Component type="Animator" />
        <Component type="Collider" />
        <Component type="Rigidbody" />
        <Component type="Script" scriptName="PlayerController" />
        <Component type="Audio" />
      </GameObject>

      <GameObject name="MainCamera">
        <Component type="Transform" />
        <Component type="Camera" />
        <Component type="Audio" />
      </GameObject>

      <GameObject name="Ground">
        <Component type="Transform" />
        <Component type="SpriteRenderer" />
        <Component type="Collider" />
      </GameObject>
    </Layer>

    <Layer name="UI">
      <GameObject name="HUD">
        <Component type="Transform" />
        <Component type="Script" scriptName="HUDController" />
      </GameObject>
    </Layer>
  </Scene>
</SceneManager>
### 만들어 본 게임 엔진을 이용한 2d 마리오 구현(영상 파일)
자체 제작 엔진을 이용하여 2d 마리오를 구현하였다.
3개의 단계를 구현하였고 마리오에 나오는 몬스터 외에도 다른 게임 속에 등장하는 몬스터를 배치하였고 움직이는 발판, 트램펄린, 불 막대와 같은 장애물을 구현해 보았다.

