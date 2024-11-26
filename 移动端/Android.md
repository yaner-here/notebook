# §0 速查表

| 安卓父版本 | 安卓子版本            | API级别 | 系统代号               |
| ---------- | --------------------- | ------- | ---------------------- |
| Android 1  | Android 1.0           | 1       | Base                   |
|            | Android 1.1           | 2       | Base_1_1               |
|            | Android 1.5           | 3       | Cupcake                |
|            | Android 1.6           | 4       | Donut                  |
| Android 2  | Android 2.0.0         | 5       | Eclair                 |
|            | Android 2.0.1         | 6       | Eclair_0_1             |
|            | Android 2.1           | 7       | Eclair_MR1             |
|            | Android 2.2           | 8       | Froyo                  |
|            | Android 2.3 ~ 2.3.2   | 9       | Gingerbread            |
|            | Android 2.3.3 ~ 2.4.4 | 10      | Gingerbread_MR1        |
| Android 3  | Android 3.0           | 11      | Honeycomb              |
|            | Android 3.1           | 12      | Honeycomb_MR1          |
|            | Android 3.2           | 13      | Honeycomb_MR2          |
| Android 4  | Android 4.0 ~ 4.0.2   | 14      | Ice_Cream_Sandwich     |
|            | Android 4.0.3 ~ 4.0.4 | 15      | Ice_Cream_Sandwich_MR1 |
|            | Android 4.1           | 16      | Jelly_Bean             |
|            | Android 4.2           | 17      | Jelly_Bean_MR1         |
|            | Android 4.3           | 18      | Jelly_Bean_MR2         |
|            | Android 4.4           | 19      | Kitkat                 |
|            | Android 4.4W          | 20      | Kitkat_Watch           |
| Android 5  | Android 5.0           | 21      | Lollipop               |
|            | Android 5.1           | 22      | Lollipop_MR1           |
| Android 6  | Android 6.0           | 23      | M (Marshmallow)        |
| Android 7  | Android 7.0           | 24      | N (Nougat)             |
|            | Android 7.1           | 25      | N_MR1                  |
| Android 8  | Android 8.0           | 26      | O (Oreo)               |
|            | Android 8.1           | 27      | O_MR1                  |
| Android 9  | Android 9.0           | 28      | P (Pie)                |
| Android 10 | Android 10            | 29      | Q (Quince Tart)        |
| Android 11 | Android 11            | 30      | R (Red Velvet Cake)    |
| Android 12 | Android 12            | 31      | S (Snow Cone)          |
| Android 13 | Android 13            | 32      | T (Tiramisu)           |

# §1 实战项目

## §1.1 GeoQuiz

### §1.1.1 用户界面设计

应用的界面由以下两点组成：

- `activity`是Android SDK中`Activity`类的一个实例，负责管理用户与界面的交互。应用的功能通过编写`Activity`的子类来实现。
- 布局(`layout`)定义了一系列界面对象，并规定了他们在屏幕上的显示位置，储存在`.xml`文件中。

### §1.1.2 视图层级结构

组建包含在视图(View)对象的层级结构中，这种结构称为视图层级结构(View Hierarchy)。

例如对于下列xml文档：

```xml
<LinearLayout xmlns:android="http://schemas.android.com/apk/res/android" 
              android:layout_width="match_parent"
              android:layout_height="match_parent"
              android:gravity="center" 
              android:orientation="vertical" >
	<TextView 
		android:layout_width="wrap_content" 
        android:layout_height="wrap_content" 
        android:padding="24dp" 
        android:text="@string/question_text" />
	<LinearLayout 
        android:layout_width="wrap_content" 
        android:layout_height="wrap_content" 
        android:orientation="horizontal" >
		<Button 
        	android:layout_width="wrap_content" 
            android:layout_height="wrap_content" 
            android:text="@string/true_button" />
		<Button 
            android:layout_width="wrap_content" 
            android:layout_height="wrap_content" 
            android:text="@string/false_button" />
	</LinearLayout>
</LinearLayout>
```

其视图层级结构可表示为：

```mermaid
flowchart TB
	subgraph LinearLayout_1 [LinearLayout]
		a1["
			xmlns:android=#quot;http://schemas.android.com/apk/res/android<br>
			android:layout_width=&quotmatch_parent&quot<br>	
            android:layout_height=&quotmatch_parent&quot<br>
            android:gravity=&quot;center&quot;<br>
            android:orientation=&quot;vertical&quot;
		"]
		subgraph TextView_1 [TextView]
			a2["
				android:layout_width=&quot;wrap_content&quot;<br>
				android:layout_height=&quot;wrap_content&quot;<br>
				android:padding=&quot;24dp&quot;<br>
				android:text=&quot;@string/question_text&quot;<br>
			"]
		end
		subgraph LinearLayout_2 [LinearLayout]
		
			a3["
				android:layout_width=&quot;wrap_content&quot;<br>
				android:layout_height=&quot;wrap_content&quot;<br>
				android:orientation=&quot;horizontal&quot;
			"]
			subgraph Button_1 [Button]
				a4["
					android:layout_width=&quot;wrap_content&quot;<br>
					android:layout_height=&quot;wrap_content&quot;<br>
					android:text=&quot;@string/true_button&quot;
				"]
			end
			subgraph Button_2 [Button]
				a5["
					android:layout_width=&quot;wrap_content&quot;<br>
					android:layout_height=&quot;wrap_content&quot;<br>
					android:text=&quot;@string/true_button&quot;
				"]
			end
		end
	end
```

### §1.1.3 根元素

XML文件只能有一个根元素，且必须指定`Android XML`资源文件的命名空间属性。

### §1.1.4 组件属性

#### §1.1.4.1 `android:layout_width`和`android:layout_height`

`android:layout_width`和`android:layout_height`分别用于规定组件的宽度和高度，几乎所有组件都需要`android:layout_width`和`android:layout_height`。这种属性有以下取值：

- `match_parent`：视图与父视图大小相同
- `wrap_content`：视图根据其显示的内容自动调整大小
- ~~`fill_parent`~~：视图与父视图大小相同，与`match_parent`作用完全一致，在API 8被弃用。

根组件的这两个属性均被强制设定为`match_parent`。虽然根组件不从属于任何一个组件，但是永远从属于Android提供的父视图。其他组件的这两个属性默认设置为`wrap_content`。

#### §1.1.4.2 `android:orientation`

 `android:orientation`属性决定`LinearLayout`组件如何排列其内部包含的组件。该属性有以下两种取值：

- `vertical`：垂直放置子组件
- `horizontal`：水平放置子组件

#### §1.1.4.3 `android:text`

`TextView`和`Button`组件均具有`android:text`，用于指定该组件要显示的文字内容。其属性值可以是字符串本身（硬编码，例如`android:text="ABC123"`），也可以是对字符串资源的引用（例如`android:text="@string/strName"`）。

字符串资源存储于一个独立的`strings.xml`中，位于`app/res/values`目录内。该文件默认包含一个`<resources>`根元素，内含众多`<string>`子元素。

```xml
<resources>
    <string name="app_name">GeoQuiz</string>
    <string name="question_text">Canberra is the capital of Australia</string>
    <string name="true_button">True</string>
    <string name="false_button">False</string>
</resources>
```

### §1.1.5 视图类

在创建Activity文件时，IDE会在`app/java/com.xxx.xxx`目录下创建一个同名`.java`文件，默认如下所示：

```java
//确定包所属位置
package com.example.geoquiz;

//androidx.appcompat.app.AppcompatActivity是Activity类的一个子类,能为旧版Android提供兼容支持
import androidx.appcompat.app.AppCompatActivity;
import android.os.Bundle;

public class MainActivity extends AppCompatActivity {
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
    }
}
```

按照§1.4创建按钮的资源ID后，就可以编写代码了：

```java
package com.example.geoquiz;
import androidx.appcompat.app.AppCompatActivity;
import android.os.Bundle;
import android.widget.Button; // 导入Button类
import android.view.View; // 导入View类
import android.widget.Toast; // 导入Toast类,用于弹出消息
public class MainActivity extends AppCompatActivity{
    private Button mTrueButton; // 按照Android变成规范,在变量名前加m
    private Button mFalseButton;
    @Override protected void onCreate(Bundle savedInstanceStata){
        // ...
        mTrueButton = (Button) findViewById(R.id.true_button); // 必须将View类型校正为Button
        mFalseButton = (Button) findViewById(R.id.false_button);
        mTrueButton.setOnClickListener(new View.OnClickListener(){ // 设置监听器
            @Override public void onClick(View v){
                Toast.makeText(
                        MainActivity.this,
                        R.string.correct_toast,
                        Toast.LENGTH_SHORT
                ).show();
            }
        });
        mFalseButton.setOnClickListener(new View.OnClickListener(){
            @Override public void onClick(View v){
                Toast.makeText(
                        MainActivity.this,
                        R.string.incorrect_toast,
                        Toast.LENGTH_SHORT
                ).show();
            }
        });
    }
}
```

### §1.1.6 资源

资源是APP中以非代码形式储存的内容，例如多媒体文件、XML文件等，一律存储于`app/res`目录中。为调用资源，我们既可以像`android:text`属性那样使用`@string/strName`，也可以使用资源ID。

在旧版本Android Studio中，资源ID存储在`app/build/generated/source/r/debug/R.java`中；在新版本Android Studio中，资源ID储存在`app/build/intermediates/runtime_symbol_list/debug/R.txt`中。每次编译时，IDE都会自动生成或更新一份存储资源ID的文件。所以修改资源后，`R.txt`不会立刻时时刷新，直到下一次编译才会重新生成。同时因为这些资源ID由系统自动生成，所以不能对它们进行手动修改。

```java
int anim abc_fade_in 0x7f010000
int anim abc_fade_out 0x7f010001
int anim abc_grow_fade_in_from_bottom 0x7f010002
int anim abc_popup_enter 0x7f010003
int anim abc_popup_exit 0x7f010004
// ...
int string false_button 0x7f0e0027 // line 1892
// ...
int string question_text 0x7f0e0051 // line 1889
int string search_menu_title 0x7f0e0052
int string status_bar_notification_info_overflow 0x7f0e0053
int string true_button 0x7f0e0054 // line 1892
// ...
int styleable ViewStubCompat_android_inflatedId 2
int xml standalone_badge 0x7f110000
int xml standalone_badge_gravity_bottom_end 0x7f110001
int xml standalone_badge_gravity_bottom_start 0x7f110002
int xml standalone_badge_gravity_top_start 0x7f110003
```

资源ID的出现，使得除了在XML中利用相对路径引用资源之外，在Java中利用面向对象的语法来引用资源成为可能。

```java
// XML
android:text="@string/app_name"
// Java
setTitle(R.string.app_name); // R即为上文介绍的R.java或R.txt
```

为了给XML文件中的组件生成资源ID，需要在定义组建时添加`android:id`属性。之所以给该属性设置的值为`@+id/elementID`而非`@id/elementID`，是因为我们是在创建资源ID，而非引用资源ID。

```xml
<Button
    android:id="@+id/true_button"
    android:layout_width="wrap_content"
    android:layout_height="wrap_content"
    android:text="@string/true_button"/>
<Button
    android:id="@+id/false_button"
    android:layout_width="wrap_content"
    android:layout_height="wrap_content"
    android:text="@string/false_button"/>
```

### §1.1.7 添加问题

创建一个`Question`类，用于表示对每一道习题的抽象形式。

```java
package com.example.geoquiz;
public class Question {
    private int mTextResId;
    private boolean mAnswerTrue;
    public int getTextResId() {
        return mTextResId;
    }
    public void setTextResId(int textResId) {
        mTextResId = textResId;
    }
    public boolean isAnswerTrue() {
        return mAnswerTrue;
    }
    public void setAnswerTrue(boolean answerTrue) {
        mAnswerTrue = answerTrue;
    }
    public Question(int textResId, boolean answerTrue){
        mTextResId = textResId;
        mAnswerTrue = answerTrue;
    }
}
```

使用`Question`类更新`Activity`类：

```java
// ...
public class MainActivity extends AppCompatActivity {
    private Button mTrueButton;
    private Button mFalseButton;
    private Button mNextButton; // 添加下一个按钮
    private TextView mQuesitonTextView;

    private Question[] mQuestionBank = new Question[]{ // 提前硬编码习题
            new Question(R.string.question_australia,true),
            new Question(R.string.question_oceans,true),
            new Question(R.string.question_mideast,false),
            new Question(R.string.question_africa,false),
            new Question(R.string.question_americas,true),
            new Question(R.string.question_asia,true),
    };
    private int mCurrentIndex = 0; // 记录当前习题序号

    @Override
    protected void onCreate(Bundle savedInstanceState) {
		//...
        mQuesitonTextView = (TextView) findViewById(R.id.question_text_view);
        updateQuestion();
        mTrueButton = (Button) findViewById(R.id.true_button);
        mFalseButton = (Button) findViewById(R.id.false_button);
        mNextButton = (Button) findViewById(R.id.next_button);
        mTrueButton.setOnClickListener(new View.OnClickListener(){
            @Override public void onClick(View v){ // 使用封装函数checkAnswer()
                checkAnswer(true);
            }
        });
        mFalseButton.setOnClickListener(new View.OnClickListener(){
            @Override public void onClick(View v){ // 使用封装函数checkAnswer()
                checkAnswer(false);
            }
        });
        mNextButton.setOnClickListener(new View.OnClickListener(){
            @Override public void onClick(View v){ // 当前问题序号+1并更新问题
                mCurrentIndex = (mCurrentIndex + 1) % mQuestionBank.length;
                updateQuestion();
            }
        });
    }
    private void updateQuestion(){ // 按照当前序号更新习题
        int question = mQuestionBank[mCurrentIndex].getTextResId();
        mQuesitonTextView.setText(question);
    }
    private void checkAnswer(boolean userPressedTrue){ // 检测userPressedTrue和isAnswerTrue是否一致
        boolean answerIsTrue = mQuestionBank[mCurrentIndex].isAnswerTrue();
        int messageResId = 0;
        if(userPressedTrue == answerIsTrue){
            messageResId = R.string.correct_toast;
        }else{
            messageResId = R.string.incorrect_toast;
        }
        Toast.makeText(MainActivity.this,messageResId,Toast.LENGTH_SHORT).show();
    }
}
```

在`String.xml`中添加对应的字符串资源：

```xml
<resources>
    <string name="app_name">GeoQuiz</string>
    <string name="question_australia">Canberra is the capital of Australia</string>
    <string name="question_oceans">The Pacific Ocean is larger than the Atlantic Ocean</string>
    <string name="question_mideast">The Suez Canal connects the Red Sea and the Indian Ocean</string>
    <string name="question_africa">The source of the Nile River is in Egypt</string>
    <string name="question_americas">The Amazon River is the longest river in the Americas</string>
    <string name="question_asia">Lake Baikal is the world\'s oldest and deepest freshwater lake.</string>
    <string name="true_button">True</string>
    <string name="false_button">False</string>
    <string name="next_button">Next</string>
    <string name="correct_toast">Correct!</string>
    <string name="incorrect_toast">Incorrect!</string>
</resources>
```

### §1.1.8 `Activity`的生命周期

每个`Activity`实例都有生命周期，在其生命周期内按照以下关系在运行、暂停、停止、不存在这四种状态间转换。



```mermaid
flowchart TB
	a1((不存在))
	a1--"onCreate()"-->a2
	a2--"onDestory()"-->a1
	subgraph b1 ["整个生命周期<br>对象实例在内存中"]
		a2((停止))
		a2--"onStart()"-->a3
		a3--"onStop()"-->a2
		subgraph b2 ["可视生命周期<br>视图部分或全部可见"]
			a3((暂停))
			a3--"onResume()"-->a4
			a4--"onPause()"-->a3
			subgraph b3 ["前台生命周期<br>用于与当前Activity交互"]
				a4((运行))
			end
		end
	end
```

| `Activity`状态 | 是否有内存实例 | 用户是否可见 | 是否处于前台 |
| -------------- | -------------- | ------------ | ------------ |
| 不存在         | ×              | ×            | ×            |
| 停止           | √              | ×            | ×            |
| 暂停           | √              | √或⍻         | ×            |
| 运行           | √              | √            | √            |

`OnCreate()`负责：

- 将组件实例化，并调用`setContentView(int)`将组件放置在屏幕上
- 引用已经实例化的组件
- 为组建设置监听器
- 访问外部模型数据

### §1.1.9 修复旋转屏幕导致Activity销毁的BUG

由生命周期的内容可知，旋转屏幕时会将当前`Activity`实例销毁，从而自动跳转到第一个问题。因此，我们需要对宽屏进行适配。

首先，创建一个给宽屏使用的XML布局文件，存放在目录`app/src/main/res/layout-land`目录下：

```xml
<?xml version="1.0" encoding="utf-8"?>
<FrameLayout xmlns:android="http://schemas.android.com/apk/res/android"
    android:layout_width="match_parent"
    android:layout_height="match_parent">
    <TextView
        android:id="@+id/question_text_view"
        android:layout_width="wrap_content"
        android:layout_height="wrap_content"
        android:layout_gravity="center_horizontal"
        android:padding="24dp" />
    <LinearLayout
        android:layout_width="wrap_content"
        android:layout_height="wrap_content"
        android:layout_gravity="center_vertical|center_horizontal"
        android:orientation="horizontal">
        <Button
            android:id="@+id/true_button"
            android:layout_width="wrap_content"
            android:layout_height="wrap_content"
            android:text="@string/true_button"
            style="?android:attr/buttonBarButtonStyle" />
        <Button
            android:id="@+id/false_button"
            android:layout_width="wrap_content"
            android:layout_height="wrap_content"
            android:text="@string/false_button"
            style="?android:attr/buttonBarButtonStyle" />
    </LinearLayout>
    <FrameLayout
        android:layout_width="wrap_content"
        android:layout_height="wrap_content"
        android:orientation="horizontal"
        android:layout_gravity="bottom|right">
        <LinearLayout
            android:layout_width="wrap_content"
            android:layout_height="wrap_content"
            android:orientation="horizontal">
            <Button
                android:layout_width="wrap_content"
                android:layout_height="wrap_content"
                android:id="@+id/previous_button"
                android:text="@string/previous_button"
                android:drawableStart="@drawable/arrow_left"
                android:drawablePadding="4sp"/>
            <Button
                android:layout_width="wrap_content"
                android:layout_height="wrap_content"
                android:id="@+id/next_button"
                android:text="@string/next_button"
                android:drawableEnd="@drawable/arrow_right"
                android:drawablePadding="4dp"/>
        </LinearLayout>
    </FrameLayout>
</FrameLayout>
```

> 注意：这里我们使用了`<FrameLayout>`标签，设置其`android:layout_gravity`属性，将跳转按钮放置在屏幕的最右下角，而这是`<LinearLayout>`做不到的。

接着，我们需要创建一个可以被多个`Activity`实例共享的变量，用于存储当前的问题序号。`Bundle`数据类型存储着字符串值与限定类型之间的映射关系，在`@Override protected void onCreate(Bundle savedInstanceState)`中我们就使用过这种数据类型。可以覆盖`onSaveInstanceState(Bundle)`方法，将所需变量保存到`Bundle`中：

```java
public class MainActivity extends AppCompatActivity{
    // ...
    private static final String KEY_INDEX = "index";
	// ...
    @Override protected void onCreate(Bundle savedInstanceState){
        // ...
        if(savedInstanceState != null){
            mCurrentIndex = savedInstanceState.getInt(KET_INDEX,0);
        }
        // ...
    }
    @Override public void onSaveInstanceState(Bundle savedInstanceState){
        super.onSaveInstanceState(savedInstanceState);
        Log.i(TAG,"onSaveInstanceState");
        savedInstanceState.putInt(KEY_INDEX,mCurrentIndex);
    }
    // ...
}
```

### §1.1.10 创建新`Activity`

首先准备字符串资源：

```xml
<resource>
	<!-- ... -->
    <string name="warning_text">Are you sure you want to do this?</string>
    <string name="show_answer_button">Show Answer</string>
    <string name="cheat_button">Cheat!</string>
    <string name="judgment_toast">Cheating is wrong.</string>
</resource>
```

创建新`Activity`的过程至少涉及三个文件的更新：Java类文件、XML布局文件和APP本身的manifest文件。这三个文件关联密切，一旦出错就会导致难以撤回的灾难。Android Studio提供了新建`Activity`向导的功能，免去了出错的风险。

`AndroidManifest.xml`文件位于`app/manifests`目录内，记录了该APP内包含的所有资源，包括刚才新建的Activity：

```xml
<manifest xmlns:android="http://schemas.android.com/apk/res/android"
    package="com.example.geoquiz">
    <application
        android:allowBackup="true"
        android:icon="@mipmap/ic_launcher"
        android:label="@string/app_name"
        android:roundIcon="@mipmap/ic_launcher_round"
        android:supportsRtl="true"
        android:theme="@style/Theme.GeoQuiz">
        <!-- 新建的Activity -->
        <activity
            android:name=".CheatActivity"
            android:exported="false" />
        <!-- 原有的的Activity -->
        <activity android:name=".MainActivity">
            <intent-filter>
                <action android:name="android.intent.action.MAIN" />
                <category android:name="android.intent.category.LAUNCHER" />
            </intent-filter>
        </activity>
    </application>
</manifest>
```

`Intent`是`component`用于与操作系统通信的媒介工具。`component`包括`Activity`、`Service`、`Broadcast`、`ContentReciver`、`ContentProvider`等一系列安卓自带的组件。`Intent`类的构造函数`Intent(Context packageContext,class<?> cls)`接受两个形参，`packageContext`接受当前`Activity`类的实例，`cls`接受要打开的`Activity`对应的类对象：

```java
Intent intent = new Intent(MainActivity.this,CheatActivity.class);
```

为了在多个`Activity`之间传递数据，我们可以使用`Intent.putExtra(String name,boolean value)`的方法将数据写入`Intent`实例中。该方法返回`Intent`实例自身，因此可以实现链式调用：

```java
intent.putExtra("data1",true)
    .putExtra("data2",false)
    .putExtra("data3",true);
```

新建的`Activity`可以使用`getIntent()`方法获得传递的`Intent`实例，然后再调用`Intent.getBooleanExtra(String name,boolean defaultValue)`来获得对应的变量：

```java
private boolean mAnswerIsTrue;
mAnswerIsTrue = getIntent().getBooleanExtra(EXTRA_ANSWER_IS_TRUE,false);
```

在多个`Activity`之间最简单的切换方式是调用`startActivity(Intent)`方法。

```java
package com.example.geoquiz;

import androidx.appcompat.app.AppCompatActivity;

import android.content.Context;
import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;

import java.awt.font.TextAttribute;

public class CheatActivity extends AppCompatActivity {
    private boolean mAnswerIsTrue;
    private TextView mAnswerTextView;
    private Button mShowAnswerButton;
    private static final String EXTRA_ANSWER_IS_TRUE = "com.example.geoquiz.answer_is_true";
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_cheat);

        mAnswerIsTrue = getIntent().getBooleanExtra(EXTRA_ANSWER_IS_TRUE,false);
        mAnswerTextView = (TextView) findViewById(R.id.answer_text_view);
        mShowAnswerButton = (Button) findViewById(R.id.show_answer_button);
        mShowAnswerButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                if(mAnswerIsTrue){
                    mAnswerTextView.setText(R.string.true_button);
                }else{
                    mAnswerTextView.setText(R.string.false_button);
                }
            }
        });
    }
    public static Intent newIntent(Context packageContext, boolean answerIsTrue){
        Intent intent = new Intent(packageContext,CheatActivity.class);
        intent.putExtra(A"com.example.geoquiz.answer_is_true",answerIsTrue);
        return intent;
    }
}
```

```java
public class MainActivity extends AppCompatActivity{
    // ...
    private Button mCheatButton;
    // ...
    @Override protected void onCreate(Bundle savedInstanceState){
        // ...
        mCheatButton = (Button) findViewById(R.id.cheat_button);
    	mCheatButton.setOnClickListener(new View.OnClickListener(){
            boolean answerIsTrue = mQuestionBank[mCurrentIndex].isAnswerTrue();
            Intent intent = CheatActivity.newIntent(MainActivity.this,answerIsTrue);
            startActivity(intent);
        });
    }
}
```

作弊功能已完成，现在添加判断是否作弊的功能。

除了`startActivity(Intent)`方法外，`startActivityForResult(Intent intent,int requestCode)`也能实现`Activity`间的切换，并且开发者可以自行设置请求代码`requestCode`，先传给子`Activity`再传给父`Activity`，以此来实现`Activity`间的交互。为此，修改`mCheatButton`监听器：

```java
mCheatButton.setOnClickListener(new View.OnClickListener() {
    @Override
    public void onClick(View v) {
        boolean answerIsTrue = mQuestionBank[mCurrentIndex].isAnswerTrue();
        Intent intent = CheatActivity.newIntent(MainActivity.this,answerIsTrue);
        startActivityForResult(intent,REQUEST_CODE_CHEAT);
    }
});
```

子`Activity`向父`Activity`发送返回信息有以下两种方法：

```java
public final void setResult(int resultCode)
public final void setResult(int resultCode,Intent intent)
/** resultCode常量既可以使用自定义的常量,也可以使用自带的常量:
 *  Activity.RESULT_OK
 *  Activity.RESULT_CANCELED
 **/
```

最终代码如下：

```java
package com.example.geoquiz;
import androidx.appcompat.app.AppCompatActivity;
import android.content.Context;
import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;
import java.awt.font.TextAttribute;
public class CheatActivity extends AppCompatActivity {
    private boolean mAnswerIsTrue;
    private TextView mAnswerTextView;
    private Button mShowAnswerButton;
    private static final String EXTRA_ANSWER_IS_TRUE = "com.example.geoquiz.answer_is_true";
    private static final String EXTRA_ANSWER_SHOWN = "com.example.geoquiz.answer_shown";
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_cheat);

        mAnswerIsTrue = getIntent().getBooleanExtra(EXTRA_ANSWER_IS_TRUE,false);
        mAnswerTextView = (TextView) findViewById(R.id.answer_text_view);
        mShowAnswerButton = (Button) findViewById(R.id.show_answer_button);
        mShowAnswerButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                if(mAnswerIsTrue){
                    mAnswerTextView.setText(R.string.true_button);
                }else{
                    mAnswerTextView.setText(R.string.false_button);
                }
                setAnswerShowResult(true);
            }
        });
    }
    public static Intent newIntent(Context packageContext, boolean answerIsTrue){
        Intent intent = new Intent(packageContext,CheatActivity.class);
        intent.putExtra(EXTRA_ANSWER_IS_TRUE,answerIsTrue);
        return intent;
    }
    public static boolean wasAnswerShown(Intent result){
        return result.getBooleanExtra(EXTRA_ANSWER_SHOWN,false);
    }
    private void setAnswerShowResult(boolean isAnswerShown){
        Intent intent = new Intent();
        intent.putExtra(EXTRA_ANSWER_SHOWN,isAnswerShown);
        setResult(RESULT_OK,intent);
    }
}
```

```java
public class MainActivity extends AppCompatActivity{
    // ...
    @Override public void onActivityResult(int requestCode, int resultCode, Intent intent) {
        super.onActivityResult(requestCode, resultCode, intent);
        if (resultCode != Activity.RESULT_OK) {
            return;
        }
        if (intent == null) {
            return;
        } else {
            mIsCheater = CheatActivity.wasAnswerShown(intent);
        }
    }
    // ...
}
```

## §1.2 CriminalIntent

### §1.2.1 `Fragment`的创建和托管

在GeoQuiz项目中，我们使用`Activity`完成了整个项目的开发。但是`Activity`有一个致命的缺陷：同屏只能有一个`Activity`运行。如果我们想设计一个QQ HD类似的界面，左侧较窄，排列着当前的联系人，右侧较宽，为聊天界面，`Activity`就无法实现这种效果。该项目将使用`Fragment`来实现上述效果。

`Fragment`在API 11被引入，有原生版本和支持库版本之分。原生版本为系统自带的，定义于`android.app`，在不同系统上的实现过程略有差别，界面也会有所差异。为了保证界面统一，我们使用支持库版本。支持库版本的`Fragment`定义在`AppCompat`库的`android.support.v4.app`或`androidx.fragment.app.Fragment`类中，必须在`build.bundle`中添加该库的依赖：

```json
// ...
dependencies {
    implementation 'androidx.appcompat:appcompat:1.2.0'
    // ...
}
```

`Activity`托管`Fragment`有两种方式：

- 在`Activity`的布局中添加`Fragment`：简单但不够灵活，在`Activity`的生命周期内无法替换`Fragment`视图
- 在`Activity`的代码中添加`Fragment`：复杂但能动态控制`Fragment`视图

这里我们对组件的灵活性要求特别高，因此我们选择在`Activity`的代码中添加`Fragment`。

定义用于存储犯罪时间的`Crime.java`类：

```java
package com.example.criminalintent;
import java.util.Date;
import java.util.UUID;
public class Crime {
    private UUID mId;
    private String mTitle;
    private Date mDate;
    private boolean mSolved;

    public Crime(){
        mId = UUID.randomUUID();
        mDate = new Date();
    }

    public UUID getId(){
        return mId;
    }
    public String getTitle(){
        return mTitle;
    }
    public void setTitle(String title){
        mTitle = title;
    }
    public Date getDate(){
        return mDate;
    }
    public void setDate(Date date){
        mDate = date;
    }
    public boolean isSolved(){
        return mSolved;
    }
    public void setSolved(boolean solved){
        mSolved = solved;
    }
}
```

添加用于创建罪行的`fragment_crime.xml`：

```xml
<?xml version="1.0" encoding="utf-8"?>
<LinearLayout xmlns:android="http://schemas.android.com/apk/res/android"
    android:orientation="vertical"
    android:layout_width="match_parent"
    android:layout_height="match_parent"
    android:layout_margin="16dp">
    <TextView
        android:layout_width="match_parent"
        android:layout_height="wrap_content"
        style="?android:listSeparatorTextViewStyle"
        android:text="@string/crime_title_label"/>
    <EditText
        android:layout_width="match_parent"
        android:layout_height="wrap_content"
        android:id="@+id/crime_title"
        android:hint="@string/crime_title_hint"/>
    <TextView
        android:layout_width="match_parent"
        android:layout_height="wrap_content"
        android:id="@+id/crime_date"
        android:text="@string/crime_details_label"/>
    <Button
        android:layout_width="match_parent"
        android:layout_height="wrap_content"
        android:id="@id/crime_date"/>
    <CheckBox
        android:layout_width="match_parent"
        android:layout_height="wrap_content"
        android:id="@+id/crime_solved"
        android:text="@string/crime_solved_label"/>
</LinearLayout>
```

创建用于容纳整个界面的总`Activity`：

```xml
<?xml version="1.0" encoding="utf-8"?>
<FrameLayout xmlns:android="http://schemas.android.com/apk/res/android"
    android:layout_width="match_parent"
    android:layout_height="match_parent"
    android:id="@+id/fragment_container">
</FrameLayout>
```

与`Activity`不同，`Fragment`布局的创建不像`public void Activity.onCreate(Bundle)`一样由`Fragment.onCreate(Bundle savedInstanceState)`创建，而是由`public View onCreateView(LayoutInflater infalter,ViewGroup container,Bundle savedInstanceState)`创建的：

```java
package com.example.criminalintent;

import android.os.Bundle;
import androidx.annotation.Nullable;
import androidx.fragment.app.Fragment;

public class CrimeFragment extends Fragment {
    private Crime mCrime;
    @Override public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        mCrime = new Crime();
    }
    @Override public View onCreateView(LayoutInflater inflater, ViewGroup container,Bundle savedInstanceState){
        View v = inflater.inflate(R.layout.fragment_crime,container,false);
        return v;
    }
}

```

此处`onCreateView(LayoutInflater,ViewGroup,Bundle)`方法实例化`Fragment`视图的布局`View`，并将其作为返回值托管给`Activity`。

接下来，我们给文本框添加一个监视器，一旦检测到文本有变化，就将新文本同步到`Crime`对象的`mTitle`字段中：

```java
// ...
private EditText mTitleField;
// ...
@Override public View onCreateView(LayoutInflater inflater, ViewGroup container,Bundle savedInstanceState){
    // ...
    mTitleField = (EditText) v.findViewById(R.id.crime_title);
    mTitleField.addTextChangedListener(new TextWatcher() {
        @Override public void beforeTextChanged(CharSequence charSequence, int start, int count, int after) {
        
        }
        @Override public void onTextChanged(CharSequence charSequence, int start, int before, int count) {
            mCrime.setTitle(charSequence.toString());
        }
        @Override public void afterTextChanged(Editable editable) {
        
        }
    });
    // ...
}
```

同理，使用代码的方式设置`Button`。

```java
// ...
private Button mDateButton;
// ...
@Override public View onCreateView(LayoutInflater inflater, ViewGroup container,Bundle savedInstanceState){
    // ...
	mDateButton = (Button) v.findViewById(R.id.crime_date);
	mDateButton.setText(mCrime.getDate().toString());
	mDateButton.setEnabled(false);
    // ...
}
```

最后，给`CheckBox`组件设置监听器，实时更新`mSolved`变量：

```java
// ...
private CheckBox mSolvedCheckBox;
// ...
@Override public View onCreateView(LayoutInflater inflater, ViewGroup container,Bundle savedInstanceState){
    // ...
    mSolvedCheckBox = (CheckBox) v.findViewById(R.id.crime_solved);
    mSolvedCheckBox.setOnCheckedChangeListener(new CompoundButton.OnCheckedChangeListener() {
        @Override public void onCheckedChanged(CompoundButton compoundButton, boolean isChecked) {
            mCrime.setSolved(isChecked);
        }
    });
    // ...
}
```

`Fragment`已经配置完毕了，现在要将其添加给`Activity`。

`Activity`类中定义了`FragmentManager`类，负责管理`Fragment`并将其对应的视图添加到`Activity`实例中：

```java
public class CrimeActivity extends AppCompatActivity {
    @Override protected void onCreate(Bundle savedInstanceState) {
        // ...
        FragmentManager fm = getSupportFragmentManager();
        Fragment fragment = fm.findFragmentById(R.id.fragment_container);
        if(fragment == null){
            fragment = new CrimeFragment();
            fm.beginTransaction() // 创建并返回FragmentTransaction实例
                .add(R.id.fragment_container,fragment) // 创建事务
                .commit(); // 提交事务
        }
    }
}
```

`Fragment.beginTransction().add().commit`作用如下：

- `Fragment.beginTransaction()`创建并返回`FragmentTransaction`实例。
- `FragmentTransction.add(int containerViewId,Fragment fragment)`负责按照`containerViewId`在`FragmentManager`队列中唯一标识`fragment`，并且查找哪个XML布局文件中定义了相同的`android:id="@+id/containerViewId"`，从而在该`ContainerView`中加载`fragment`。
- `FragmentTransction.commit()`提交事务。

### §1.2.2 `Fragment`的生命周期

```mermaid
graph LR
	subgraph Create ["创建"]
		C["onActivityCreate(Bundle)"]
	end
	subgraph Stop ["停止&nbsp;Activity/Fragment再次可见"]
		D["onStart()"]
		H["onDestoryView()"]
	end
	subgraph Pause ["暂停&nbsp;Activity/Fragment重返前台"]
		E["onResume()"]
		G["onStop()"]
	end
	subgraph Run
		F["onPause()"]
	end
	subgraph "&nbsp"
		B1["onAttach(Context)"]
		B2["onCreate(bundle)"]
		B3["onCreateView()"]
	end
A[/启动/]-->B["setContentView()"]-->C-->D-->E-->F-->G-->H[Activity关闭]-->I["OnDestroy()"]-->J["onDetach()"]-->K[/销毁/]
B-->B1-->B2-->B3-->B
```

### §1.2.3 添加列表

创建`CrimeLab`类，添加静态变量`sCrimeLab`（`s`表示`static`）用于存储`Crime`对象：

```java
package com.example.criminalintent;

import android.content.Context;
import android.widget.LinearLayout;

import java.util.ArrayList;
import java.util.List;
import java.util.UUID;

public class CrimeLab {
    private static CrimeLab sCrimeLab;
    private List<Crime> mCrimes;
    public static CrimeLab get(Context context){
        if(sCrimeLab == null){
            sCrimeLab = new CrimeLab(context);
        }
        return sCrimeLab;
    }
    private CrimeLab(Context context){
        mCrimes = new ArrayList<>();
    }
    public List<Crime> getCrimes(){
        return mCrimes;
    }
    public Crime getCrime(UUID id){
        for(Crime crime : mCrimes){
            if (crime.getId().equals(id)){
                return crime;
            }
        }
        return null;
    }
    public void testCrimeLab(){
        for(int i = 0;i < 100;i++){
            Crime crime = new Crime();
            crime.setTitle("Crime #" + i);
            crime.setSolved(i % 2 == 0);
            mCrimes.add(crime);
        }
    }
}
```

这个类的特殊之处在于，`CrimeLab`的构造方法是被`private`修饰的，也就是说在其他类中无法直接创建该类的实例，必须通过该类定义的`public`方法`CrimeLab.get(Context)`才能将其实例化。

我们可以重复使用`CrimeActivity`类的代码才创建多个`CrimeListActivity`类。每次新建`Activity`时都需要重复这段代码，于是考虑将其封装成抽象类`SingleFragmentActivity`。

```java
package com.example.criminalintent;

import android.os.Bundle;
import androidx.appcompat.app.AppCompatActivity;
import androidx.fragment.app.Fragment;
import androidx.fragment.app.FragmentManager;

public abstract class SingleFragmentActivity extends AppCompatActivity {
    protected abstract Fragment createFragment();
    @Override protected void onCreate(Bundle savedInstanceState){
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_fragment);
        FragmentManager fm = getSupportFragmentManager();
        Fragment fragment = fm.findFragmentById(R.id.fragment_container);
        if(fragment == null){
            fragment = createFragment();
            fm.beginTransaction()
                    .add(R.id.fragment_container,fragment)
                    .commit();
        }
    }
}

```

这样`CrimeActivity.java`就可以进行简化了。

```java
package com.example.criminalintent;

import androidx.appcompat.app.AppCompatActivity;
import androidx.fragment.app.Fragment;
import androidx.fragment.app.FragmentManager;

import android.os.Bundle;

public class CrimeActivity extends SingleFragmentActivity {
    @Override protected Fragment createFragment(){
        return new CrimeFragment();
    }
}
```

现在运行程序，Android会解析`AndroidManifest.xml`中的`Launcher Activity`，即`CrimeListActivity`。该类内部本身没有定义`onCreate()`，于是向上追踪至其超类`SingleFragmentActivity`，执行该超类中的初始方法`SingleFragmentActivity.onCreate()`，进行了以下步骤：

- 使用`setContentView()`方法，查找项目内`id`为`activity_fragment`的XML布局文件，即`activity_fragment.xml`。该布局文件内只有一个`<FrameLayout>`标签。

- 创建一个`FragmentManager`实例，将`id`为`fragment_container`的XML布局文件（`activity_fragment.xml`）实例化，成为一个新的`Fragment`实例。

- 检测该`Fragment`实例是否为`null`（一般情况下都为是），则舍弃该实例，转而用子类中的`createFragment()`方法创建一个新`Fragment`。该方法返回一个`Fragment`的子类`CrimeListFragment`，并将其托管给`FragmentManager`。

- `CrimeListFragment`内含`onCreateView()`，每次尝试新建一个`View`实例时就会执行该方法。

  - 该方法通过`LayoutInflator.inflate(int resource,ViewGroup root,boolean attachToRoot)`将`resource`指向的`fragment_crime_list.xml`XML布局文件实例化成为一个`View`对象，然后将该`View`对象对应的XML布局文件中的`<Android.recyclerview.widget.RecyclerView>`根标签通过`(RecyclerView) view.findViewById()`方法转换成了`RecyclerView`实例，并给该实例的`setLayoutManager()`方法绑定一个即时生成的`LinearLayoutManager`实例。最后`onCreateView()`返回修改过的`View`实例。

  - 该方法会调用自定义的`updateUI()`方法，获得一个带有测试数据的`CrimeLab`实例，该实例通过内部的`List<Crime>`对象来存储多个`Crime`。该对象会被传入`CrimeAdapter`类的构造方法中产生一个实例。`CrimeAdapter`继承于`RecyclerView.Adapter<CrimeHolder>`超类，内有三个需要覆盖的方法：

    - `public CrimeHolder onCreateViewHolder()`

      将当前`Activity`的`LayoutInflator`和`ViewGroup`实例，传给`CrimeHolder`实例。这样的话在后续的代码中，每个`CrimeHolder`调用`findViewById()`时，都能用相同的`id`获得自己所包含的`View`的`TextView`实例。

    - `public void onBindViewHolder()`

      按照传入的`position`，在`List<Crime>`中查找对应的`Crime`，然后调用传来的`CrimeHolder`实例中的`bind()`方法进行绑定。

    - `public int getItemCount()`

      返回当前`CrimeApdator`中`List<Crime>`的元素个数。

    前面提到`onCreateViewHolder()`返回的是自定义类`CrimeHolder`的实例。该类继承于`RecyclerView.ViewHolder`，内部定义的`bind(Crime)`方法可将传入的`Crime`实例中的字段输出至`CrimeHolder`内`View`实例`itemView`的`<TextView>`标签中。

现在开始开发列表的界面，将`AndroidManifest.xml`中声明`CrimeListActivity`为`Launcher Activity`：

```xml
<manifest>
	<!-- ... -->
    <activity android:name=".CrimeListActivity">
        <!-- ... -->
    </activity>
    <activity android:name=".CrimeActivity">
    </activity>
    <!-- ... -->
</manifest>
```

接下来给`CrimeListFragment`做铺垫。创建`CrimeListActivity`和`CrimeListFragment`两个类：

```java
package com.example.criminalintent;

import androidx.fragment.app.Fragment;

public class CrimeListActivity extends SingleFragmentActivity {
    @Override protected Fragment createFragment(){
        return new CrimeListFragment();
    }
}
```

```java
package com.example.criminalintent;

import androidx.fragment.app.Fragment;

public class CrimeListFragment extends Fragment {

}
```

`RecyclerView`是`ViewGruop`的子类，其中每一个列表项都是由一个`View`子对象显示的。而且在加载列表项时选择分批加载，用户滑动屏幕切图时，上一个视图会被回收利用。

`ViewHolder`是`View`的子类，唯一的用途就是容纳`View`视图。

事实上，`RecyclerView`本身不能创建`ViewHolder`，这个操作是由`Adapter`完成的，负责创建`ViewHolder`并将其绑定至模型层数据。

```mermaid
graph LR
	RecyclerView[RecyclerView]
	RecyclerView-->ViewHolder1[ViewHolder]--"itemView"-->View1[View]
	RecyclerView-->ViewHolder2[ViewHolder]--"itemView"-->View2[View]
	RecyclerView-->ViewHolder3[ViewHolder]--"itemView"-->View3[View]
```

`RecyclerView`创建视图对象时，要经历以下流程：

1. 寻找`RecyclerView`的`Adapter`。
2. `RecyclerView`调用`Adapter`的`getItemCount()`方法，询问数组列表包含多少对象。
3. `RecyclerView`调用`Adapter`的`onCreateViewHolder(ViewGroup,int)`方法创建`ViewHolder`及其要显示的`View`。
4. `RecyclerHolder`将得到的`ViewHolder`传入`onBindViewHolder(ViewHolder,int)`方法中，`ViewHolder`将视图绑定在自己身上。
5. 一旦`ViewHolder`填充满了屏幕，`RecyclerView`就会停止调用`onCreateViewHolder()`方法，同时将未被渲染的`ViewHolder`回收利用以节省内存。

```mermaid
sequenceDiagram
    par 
        RecyclerView->>Adapter:getItemCount()
    and
        Adapter->>RecyclerView:100
    and
        RecyclerView->>Adapter:onCreateViewHolder(...)
    end
    par 
        Adapter->>RecyclerView:ViewHolder
    and
        RecyclerView->>Adapter:onBindViewHolder(...,0)
    end
    par 
        RecyclerView->>Adapter:onCreateViewHolder(...)
    and
        Adapter->>RecyclerView:ViewHolder
    and
        RecyclerView->>Adapter:onBindViewHolder(...,1)
    end
```

继续完善`CrimeListFragment`及其XML布局文件`fragment_crime_list.xml`：

```xml
<?xml version="1.0" encoding="utf-8"?>
<androidx.recyclerview.widget.RecyclerView
    xmlns:android="http://schemas.android.com/apk/res/android"
    android:layout_width="match_parent"
    android:layout_height="match_parent"
    android:id="@+id/crime_recycler_view">
</androidx.recyclerview.widget.RecyclerView>
```

```java
package com.example.criminalintent;
import android.os.Bundle;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.TextView;
import androidx.fragment.app.Fragment;
import androidx.recyclerview.widget.LinearLayoutManager;
import androidx.recyclerview.widget.RecyclerView;
import java.util.List;

public class CrimeListFragment extends Fragment {
    private RecyclerView mCrimeRecyclerView;
    private CrimeAdapter mAdapter;

    @Override public View onCreateView(LayoutInflater inflater, ViewGroup container, Bundle savedInstanceState){
        View view = inflater.inflate(R.layout.fragment_crime_list,container,false);
        mCrimeRecyclerView = (RecyclerView) view.findViewById(R.id.crime_recycler_view);
        mCrimeRecyclerView.setLayoutManager(new LinearLayoutManager(getActivity()));
        updateUI();
        return view;
    }
    private class CrimeHolder extends RecyclerView.ViewHolder{
        private TextView mTitleTextView;
        private TextView mDateTextView;
        private Crime mCrime;
        public CrimeHolder(LayoutInflater inflater,ViewGroup parent){
            super(inflater.inflate(R.layout.list_item_crime,parent,false));
            mTitleTextView = (TextView) itemView.findViewById(R.id.crime_title);
            mDateTextView = (TextView) itemView.findViewById(R.id.crime_title);
        }
        public void bind(Crime crime){
            mCrime = crime;
            mTitleTextView.setText(mCrime.getTitle());
            mDateTextView.setText(mCrime.getDate().toString());
        }
    }
    private class CrimeAdapter extends RecyclerView.Adapter<CrimeHolder>{
        private List<Crime> mCrimes;
        public CrimeAdapter(List<Crime> crimes){
            this.mCrimes = crimes;
        }
        @Override public CrimeHolder onCreateViewHolder(ViewGroup parent, int viewType) {
            LayoutInflater layoutInflater = LayoutInflater.from(getActivity());
            return new CrimeHolder(layoutInflater,parent);
        }

        @Override public void onBindViewHolder(CrimeHolder holder, int position) {
            Crime crime = mCrimes.get(position);
            holder.bind(crime);
        }

        @Override public int getItemCount() {
            return mCrimes.size();
        }
    }
    private void updateUI(){
        CrimeLab crimeLab = CrimeLab.get(getActivity());
        List<Crime> crimes = crimeLab.getCrimes();
        mAdapter = new CrimeAdapter(crimes);
        mCrimeRecyclerView.setAdapter(mAdapter);
    }
}
```

现在，只要获取到一个`Crime`实例，`CrimeHolder`就能刷新`TextView`。

接下来给每个`itemView`都添加一个点击监听器：

```java
public class CrimeListFragment extends Fragment {
    // ...
    private class CrimeHolder extends RecyclerView.ViewHolder implements View.OnClickListener{
        // ...
        public CrimeHolder(LayoutInflator inflater,ViewGroup parent){
            // ...
            itemView.setOnclickListener(this);
        }
        @Override public void onClick(View view){
            Toast.makeText(
            	getActivity(),
                mCrime.getTitle()+" clicked!",
                Toast.LENGTH_SHORT
            ).show();
        }
    }
}
```

### §1.2.4 图形布局工具

- `Autoconnection to Parent`：在预览界面拖拽视图时，约束会自动配置，Android Studio会推断开发者的视图布置意图，实现自动连接
- `Clear All Constraints`：清除全部约束
- `Infer Constraints`：手动配置约束。

视图尺寸支持三种类型：

| 设置类型 | 设置值         | 含义                           |
| -------- | -------------- | ------------------------------ |
| 固定大小 | `[num]dp`      | 以dp为单位，为视图指定固定值   |
| 包裹内容 | `wrap_content` | 使得尺寸刚好能容纳下包含的内容 |
| 动态适应 | `0dp`          | 允许视图缩放以满足指定约束     |

为了在右侧容纳图片，我们先点击"Convert LinearLayout to ConstraintLayout"按钮，把`<LinearLayout>`标签换成`<androidx.constraintlayout.widget.ConstraintLayout>`标签，接着把`crime_date`和`crime_title`的`layout_width`属性统一摄者为`wrap_content`，然后创建一个`ImageView`组件，将这些组件的边紧贴在边框四周，再根据自己的喜好排版，得到的XML布局文件如下：

```xml
<?xml version="1.0" encoding="utf-8"?>
<androidx.constraintlayout.widget.ConstraintLayout xmlns:android="http://schemas.android.com/apk/res/android"
    xmlns:app="http://schemas.android.com/apk/res-auto"
    xmlns:tools="http://schemas.android.com/tools"
    android:id="@+id/linearLayout"
    android:layout_width="match_parent"
    android:layout_height="wrap_content">

    <TextView
        android:id="@+id/crime_title"
        android:layout_width="0dp"
        android:layout_height="wrap_content"
        android:layout_marginStart="16dp"
        android:layout_marginTop="16dp"
        android:text="Crime Title"
        android:textColor="@color/black"
        android:textSize="18sp"
        app:layout_constraintStart_toStartOf="parent"
        app:layout_constraintTop_toTopOf="parent" />

    <TextView
        android:id="@+id/crime_date"
        android:layout_width="0dp"
        android:layout_height="wrap_content"
        android:layout_marginStart="16dp"
        android:layout_marginTop="8dp"
        android:layout_marginEnd="8dp"
        android:text="Crime Date"
        app:layout_constraintStart_toStartOf="parent"
        app:layout_constraintTop_toBottomOf="@+id/crime_title" />

    <ImageView
        android:id="@+id/crime_solved"
        android:layout_width="39dp"
        android:layout_height="wrap_content"
        android:visibility="visible"
        app:layout_constraintBottom_toBottomOf="parent"
        app:layout_constraintEnd_toEndOf="parent"
        app:layout_constraintTop_toTopOf="parent"
        app:srcCompat="@drawable/ic_solved" />

</androidx.constraintlayout.widget.ConstraintLayout>
```

现在列表中的每一项都有手铐图片，这与我们的期望不符合。首先给该`<ImageView>`标签添加一个`Id`：

```xml
<androidx.constraintlayout.widget.ConstraintLayout>
	<!-- ... -->
    <ImageView
   		android:id="@+id/crime_solved"/>
</androidx.constraintlayout.widget.ConstraintLayout>
```

然后在`CrimeListFragment.java`中添加逻辑：

```java
public class CrimeListFragment extends Fragment {
	// ...
    private class CrimeHolder extends RecyclerView.ViewHolder implements View.OnClickListener{
		// ...
        private ImageView mSolvedImageView;
        public CrimeHolder(Layout inflater,ViewGroup parent){
            // ...-`
            mSolvedImageView = (ImageView) itemView.findViewById(R.id.crime_solved);
        }
        public void bind(Crime crime){
            // ...
            mSolvedImageView.setVisibility(crime.isSolved()?View.VISIBLE:View.GONE);
        }
    }
}
```

Android SDK提供了多种像素单位：

| 像素类型   | 全称                                    | 含义                                               | 是否受DPI影响 | 是否受字体(无障碍使用)影响 |
| ---------- | --------------------------------------- | -------------------------------------------------- | ------------- | -------------------------- |
| `px`       | 像素(Pixel)                             | 一个像素单位恒对应一个屏幕像素单位                 | √             | ×                          |
| `dp`/`dip` | 密度无关像素(Density-Independent Pixel) | 指定显示在屏幕上的真实尺寸                         | ×             | ×                          |
|            | `pt`                                    | 类似于`dp`，真实尺寸以点($\frac{1}{72}$英寸)为单位 |               |                            |
|            | `mm`                                    | 类似于`dp`，真实尺寸以毫米为单位                   |               |                            |
|            | `in`                                    | 类似于`dp`，真实尺寸以英寸为单位                   |               |                            |
| `sp`       | 缩放无关像素(Scale-Independent Pixel)   | 字体大小与真实尺寸一一对应                         | ×             | √                          |

Android应用设计规范采用的是[Material Design原则](developer.android.com/design/index.html)，

接下来我们要建立列表中的项目与详情页的关系：

```mermaid
graph LR
	subgraph 第二屏;
		CrimeActivity[CrimeActivity]-->CrimeFragment[CrimeFragment]
	end
	subgraph 第一屏;
		CrimeListActivity[CrimeListActivity]-->CrimeListFragment[CrimeListFragment]
	end
	CrimeListFragment--"startActivity(...)"-->CrimeActivity
```

我们先在`CrimeListFragment.java`中建立一个跳转的逻辑：

```java
public class CrimeListFragment extends Fragment {
	// ...
	@Override public void onClick(View view){
        Intent intent = new Intent(getActivity(),CrimeActivity.class);
        startActivity(intent);
    }
}
```

接着将当前`Crime`对象传给`Activity`：

```java
/* CrimeListFragment.java */
package com.example.criminalintent;
import androidx.appcompat.app.AppCompatActivity;
import androidx.fragment.app.Fragment;
import androidx.fragment.app.FragmentManager;
import android.content.Context;
import android.content.Intent;
import android.os.Bundle;
import java.util.UUID;

public class CrimeActivity extends SingleFragmentActivity {
    public static final String EXTRA_CRIME_ID = "com.example.criminalintent.crime_id";
    public static Intent newIntent(Context packageContext, UUID crimeId){
        Intent intent = new Intent(packageContext,CrimeActivity.class);
        intent.putExtra(EXTRA_CRIME_ID,crimeId);
        return intent;
    }
    @Override protected Fragment createFragment(){
        return new CrimeFragment();
    }
}
```

```java
/* CrimeListFragment.java */
public class CrimeListFragment extends Fragment {
    // ...
    private class CrimeHolder extends RecyclerView.ViewHolder implements View.OnClickListener{
        Intent intent = CrimeActivity.newIntent(getActivity(),mCrime.getId());
        startActivity(intent);
    }
}
```

现在`crimeId`已经从`CrimeListFragment`传输到了`CrimeActivity`的`intent`中，为了在`CrimeFragment`调用该字段，我们有两种方式：

- 直接调用：

  ```java
  /* CrimeFragment.java */
  public class CrimeFragment extends Fragment {
  	@Override public void onCreate(Bundle savedInstanceState){
          super.onCreate(savedInstanceState);
          UUID crimeId = (UUID) getActivity()
              .getIntent()
              .getSerializableExtra(CrimeActivity.EXTRA_CRIME_ID);
          mCrime = CrimeLab.get(getActivity()).getCrime(crimeId);
      }
  }
  ```

  这种方法的缺点是破坏了`CrimeFragment`的封装性，因为`crimeID`是保存在`CrimeActivity.EXTRA_CRIME_ID`中的，这意味着`CrimeFragment`必须由某个特定的`Activity`托管。如果后续针对平板提出右侧显示两个`CrimeFragment`以供人工对比的需求，那么这两个`CrimeFragment`必会显示相同的内容。

- Fragment Argument

  如果能把`crimeId`存储在`CrimeArgument`中，而不是`CrimeActivity`中，就能摆脱对`Activity`的依赖了。

  ```java
  public class CrimeFragment extends Fragment {
  	// ...
      private static final String ARG_CRIME_ID = "crime_id";
      public static CrimeFragment newInstance(UUID crimeId){
          Bundle args = new Bundle();
          args.putSerializable(ARG_CRIME_ID,crimeId);
          CrimeFragment fragment = new CrimeFragment();
          fragment.setArguments(args);
          return fragment;
      }
  }
  ```

  现在其他类不会用到`EXTRA_CRIME_ID`，可以将其设为私有字段：

  ```java
  public class CrimeActivity extends SingleFragmentActivity {
      private static final String EXTRA_CRIME_ID = "com.example.criminalintent.crime_id";
  	// ...
      @Override protected Fragment createFragment(){
          UUID crimeId = (UUID) getIntent().getSerializableExtra(EXTRA_CRIME_ID);
          return CrimeFragment.newInstance(crimeId);
          // 原return new CrimeFragment();
      }
  }
  ```

  ```java
  public class CrimeFragment extends Fragment {
      @Override public void onCreate(Bundle savedInstanceState) {
          super.onCreate(savedInstanceState);
          //原UUID crimeId = (UUID) getActivity().getIntent().getSerializableExtra(CrimeActivity.EXTRA_CRIME_ID);
          UUID crimeId = (UUID) getArguments().getSerializable(ARG_CRIME_ID);
          mCrime = CrimeLab.get(getActivity()).getCrime(crimeId);
      }
  }
  ```

- 直接在`CrimeFragment`创建一个实例字段

  极其不推荐这种方法。系统会在很多情况下重建`Fragment`，其频率比重建`Activity`还频繁。回想第一个项目，光是转屏就已经够麻烦的了，现在按下Home键也会重建`Fragment`。一旦重建，储存的实例变量将不复存在，而`Fragment Argument`就是为了解决该问题而生的。

获取到`Crime`后就能调用里面的字段了：

```java
public class CrimeFragment extends Fragment {
    // ...
    @Override public View onCreateView(LayoutInflater inflater, ViewGroup container,Bundle savedInstanceState){
        // ...
        mTitleField.setText(mCrime.getTitle());
    	// ...
        mSolvedCheckBox.setChecked(mCrime.isSolved());
        // ...
    }
}
```

### §1.2.5 刷新列表项

现在按下返回键，我们发现手铐图标并没有刷新。在`CrimeListFragment`启动`CrimeActivity`实例后按下返回键时，用于托管`CrimeListFragment`的`FragmentManager`会使其重新恢复运行状态，这期间会调用其`onResume()`方法，于是我们就可以在这个方法中实现更新：

```java
public class CrimeListFragment extends Fragment {
    // ...
    @Override public void onResume(){
        super.onResume();
        updateUI();
    }
    private void updateUI(){
        CrimeLab crimeLab = CrimeLab.get(getActivity());
        List<Crime> crimes = crimeLab.getCrimes();
        if(mAdapter==null){
            mAdapter = new CrimeAdapter(crimes);
            mCrimeRecyclerView.setAdapter(mAdapter);
        }else{
            mAdapter.notifyDataSetChanged();
        }
    }
    // ...
}
```

### §1.2.6 `ViewPager`

接下来在`CrimeFragment`界面添加一个功能，向左滑或向右滑能切换到逻辑上相邻的`CrimeFragment`。

新建`CrimePagerActivity`类，让`CrimeFragment.startActivity()`方法不再新建`CrimeFragment`，而是新建`CrimePagerActivity`类，让其新建`CrimeFragment`：

```java
package com.example.criminalintent;
import android.os.Bundle;
import androidx.appcompat.app.AppCompatActivity;

public class CrimePagerActivity extends AppCompatActivity {
    @Override protected void onCreate(Bundle savedInstanceState){
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_crime_pager);
    }
}
```

```xml
<?xml version="1.0" encoding="utf-8"?>
<androidx.viewpager.widget.ViewPager xmlns="http://schemas.android.com/apk/res/android"
    layout_width="match_parent"
    layout_height="match_parent"
    id="@+id/activity_crime_pager_view_pager">
</androidx.viewpager.widget.ViewPager>
```

类似于`RecyclerView`需要借助`Adapter`提供的视图，`ViewPager`也需要`PagerAdapter`的支持：

```java
package com.example.criminalintent;
import android.os.Bundle;
import androidx.annotation.NonNull;
import androidx.appcompat.app.AppCompatActivity;
import androidx.fragment.app.Fragment;
import androidx.fragment.app.FragmentManager;
import androidx.fragment.app.FragmentStatePagerAdapter;
import androidx.viewpager.widget.ViewPager;
import java.util.List;

public class CrimePagerActivity extends AppCompatActivity {
    private ViewPager mViewPager;
    private List<Crime> mCrimes;
    @Override protected void onCreate(Bundle savedInstanceState){
        super.onCreate(savedInstanceState);
        // 设置CrimePagerActivity的XML布局
        setContentView(R.layout.activity_crime_pager);
        // 将XML布局中的根标签<ViewPager>绑定在mViewPager变量上
        mViewPager = (ViewPager) findViewById(R.id.crime_view_pager);
        // 获取对应的List<Crime>
        mCrimes = CrimeLab.get(this).getCrimes();
        // 获取当前Fragment的托管容器的管理器(FragmentManager)
        FragmentManager fragmentManager = getSupportFragmentManager();
        // 将mViewPager绑定一个FragmentStatePagerAdapter实例
        mViewPager.setAdapter(new FragmentStatePagerAdapter() {
            @Override public Fragment getItem(int position) {
                Crime crime = mCrimes.get(position);
                return CrimeFragment.newInstance(crime.getId());
            }
            @Override public int getCount() {
                return mCrimes.size();
            }
        });
    }
}
```

现在弃用`CrimeActivity`，转而使用`CrimePagerActivity`：

```java
public class CrimePagerActivity extends AppCompatActivity{
    // ...
    public static final String EXTRA_CRIME_ID = "com.example.criminalintent.crime_id";
    public static Intent newIntent(Context packageContext, UUID crimeId){
        Intent intent = new Intent(packageContext,CrimePagerActivity.class);
        intent.putExtra(EXTRA_CRIME_ID);
        return intent;
    }
    // ...
    @Override protected void onCreate(Bundle savedInstanceState){
        // ...
        UUID crimeId = (UUID) getIntent().getSerializableExtra(EXTRA_CRIME_ID);
    	// ...
    }
}
```

```java
public class CrimeListFragment extends Fragment {
    // ...
    private class CrimeHolder extends RecyclerView.ViewHolder implements View.OnClickListener{
        // ...
        @Override public void onClick(View view){
            // Intent intent = CrimeActivity.newIntent(getActivity(),mCrime.getId());
        	Intent intent = CrimePagerActivity.newIntent(getActivity(),mCrime.getId());
        	startActivity(intent);
        }
        // ...
    }
	// ...
}
```

要让APP启动`CrimePagerActivity`，还要在`AndroidManifest.xml`中声明它：

```xml
<manifest>
	<!-- ... -->
    <application>
    	<!-- ... -->
        <activity android:name=".CrimePagerActivity" />
        <!-- ... -->
    </application>
    <!-- ... -->
</manifest>
```

再删除`CrimePagerActivity`中启动的`Intent`实例：

```java
public class CrimeListFragment extends Fragment {
    // ...
    private class CrimeHolder extends RecyclerView.ViewHolder implements View.OnClickListener{
    	// ...
    	@Override public void onClick(View view){
            // Intent intent = CrimeActivity.newIntent(getActivity(),mCrime.getId());
        	Intent intent = CrimePagerActivity.newIntent(getActivity(),mCrime.getId());
        	startActivity(intent);
        }
    	// ...
	}
    // ...
}
```

`ViewPager`默认只显示第一个`crime`的明细，因此点击任意项都会跳转到第一个`crime`的明细页面，所以我们需要利用`ViewPager.setCurrentItem()`方法来进一步指定是哪个`crime`：

```java
public class CrimePagerActivity extends AppCompatActivity{
    // ...
    @Override protected void onCreate(Bundle savedInstanceState){
        // ...
        for(int i=0;i<mCrimes.size();i++){
            if(mCrimes.get(i).getId().equals(crimeId)){
                mViewPager.setCurrentItem(i);
                break;
            }
        }
    }
    // ...
}
```

### §1.2.7 对话框

引入字符串资源：

```xml
<resources>
	<!-- ... -->
    <string name="date_picker_title">犯罪日期</string>
</resources>
```

创建用于选择日期的新类`DatePickerFragment`：

```java
public class DatePickerFragment extends DialogFragment {
    @Override public Dialog onCreateDialog(Bundle savedInstanceState){
        		// 根据传入的Context创建一个AlertDialog.Builder实例
        return new AlertDialog.Builder(getActivity())
            	// 设置标题
                .setTitle(R.string.date_picker_title)
                // 设置确定按钮的监听器(现为null,待实现)
            	.setPositiveButton(android.R.string.ok,null)
                // 返回配置完成的AlertDialog实例
            	.create();
    }
}
```

在`CrimeFragment`中进行调用：

```java
public class CrimeFragment extends Fragment {
    // ...
    private static final String DIALOG_DATE = "DialogDate";
    // ...
    @Override public View onCreateView(LayoutInflater inflater,ViewGroup container,Bundle savedInstanceState){
        // ...
        // mDateButton.setEnabled(false);
        mDateButton.setOnClickListener(new View.OnClickListener(){
            @Override public void onClick(View v){
                FragmentManager manager = getFragmentManager();
                DatePickerFragment dialog = new DatePickerFragment();
                dialog.show(manager,DIALOG_DATE);
            }
        })
    }
    // ...
}
```

给对话框创建视图：

```xml
<!-- dialog_date.xml -->
<DatePicker xmlns:android="http://schemas.android.com/apk/res/android"
    android:layout_width="wrap_content"
    android:layout_height="wrap_content"
    android:id="@+id/dialog_date_picker"
    android:calendarViewShown="false">
</DatePicker>
```

给对话框绑定视图：

```java
public class DatePickerFragment extends DialogFragment {
    @Override public Dialog onCreateDialog(Bundle savedInstanceState){
        View v = LayoutInflater.from(getActivity()).inflate(R.layout.dialog_date,null);
        return new AlertDialog.Builder(getActivity())
                .setView(v)
				// ...
    }
}
```

### §1.2.8 `Fragment`之间的数据传递

```mermaid
flowchart LR
	CrimeFragment--"显示的日期"-->DatePickerFragment
	DatePickerFragment--"用户所选日期"-->CrimeFragment
```

```mermaid
sequenceDiagram
	Crime->>CrimeFragment:mCrime.getDate()
	CrimeFragment->>DatePickerFragment:newInstance(Date)
	DatePickerFragment->>CrimeFragment:onActivityResult(...)
	CrimeFragment->>Crime:mCrimes.setDate(...)
```

在`DatePickerFragment`中创建用于传递数据的`Bundle`：

```java
public class DatePickerFragment extends DialogFragment{
    private static final String ARG_DATE = "date";
    private DatePicker mDatePicker;
    public static DatePickerFragment newInstance(Date date){
        Bundle args = new Bundle();
        args.putSerializable(ARG_DATE,date);
        DatePickerFragment datePickerFragment = new DatePickerFragment();
        datePickerFragment.setArguments(args);
        return datePickerFragment;
    }
    // ...
}
```

在`CrimeFragment`中使用刚才定义的新方法来返回`DatePickerFragment`实例：

```java
public class CrimeFragment extends Fragment {
    // ...
    @Override public View onCreateView(LayoutInflater inflater,ViewGroup container,Bundle savedInstanceState){
        // ...
        mDateButton.setOnClickListener(new View.OnClickListener(){
            @Override public void onClick(View v){
                FragmentManager manager = getFragmentManager();
                // DatePickerFragment dialog = new DatePickerFragment();
                DatePickerFragment dialog = DatePickerFragment.newInstance(mCrime.getDate());
            }
        });
        // ...
    }
    // ...
}
```

`DatePickerFragment`根据传入的`Date`对象来初始化，我们还需要获得其具体的年月日：

```java
public class DatePickerFragment extends DialogFragment {
    // ...
    @Override public Dialog onCreateDialog(Bundle savedInstanceState){
        Date date = (Date) getArguments().getSerializable(ARG_DATE);
        Calendar calendar = Calendar.getInstance();
        calendar.setTime(date);
        int year = calendar.get(Calendar.YEAR);
        int month = calendar.get(Calendar.MONTH);
        int day = calendar.get(Calendar.DAY_OF_MONTH);

        View v = LayoutInflater.from(getActivity()).inflate(R.layout.dialog_date,null);
        mDatePicker = (DatePicker) v.findViewById(R.id.dialog_date_picker);
        mDatePicker.init(year,month,day,null);
    }
}
```

现在我们实现了`CrimeFragment`向`DatePickerFragment`的数据传递，接下来实现`DatePickerFragment`向`CrimeFragment`的数据传递：

```java
public class CrimeFragment extends Fragment{
	// ...
    private static final int REQUEST_DATE = 0;
    // ...
    @Override public View onCreateView(LayoutInflater inflater,ViewGroup container,Bundle savedInstanceState){
        // ...
        mDateButton.setOnClickListener(new View.OnClickListener(){
            @Override public void onClick(View v){
                // ...
                dialog.setTargetFragment(CrimeFragment.this,REQUEST_DATE);
        		dialog.show(manager,DIALOG_DATE);
            }
        })
    }
    // ...
}
```

`Activity.onActivityResult(...)`方法是`ActivityManager`在子`Activity`销毁后调用的父`Activity`方法。在父`Activity`接受到该方法后，其`FragmentManager`会调用对应的`Fragment`内的`Fragment.onActivityResult(...)`方法。

```java
public class DatePickerFragment extends DialogFragment{
    // ...
    public static final String EXTRA_DATE = "com.example.criminalintent.date";
    // ...
    private void sendResult(int resultCode,Date date){
        if(getTargetFragment() == null){
            return;
        }
        Intent intent = new Intent();
        intent.putExtra(EXTRA_DATE,date);
        getTargetFragment().onActivityResult(getTargetRequestCode(),resultCode,intent);
    }
}
```

更改日期确定按钮的监听器：

```java
public class DatePickerFragment extends DialogFragment{
    // ...
    @Override Dialog onCreateDialog(Bundle savedInstanceState){
        // ...
        return new AlertDialog(Bundle savedInstanceState)
            .setView(v)
			.setTitle(R.string.date_picker_title)
            // .setPositiveButton(android.R.string.ok,null);
            .setPositiveButton(
            	android.R.string.ok,
            	new DialogInterface.OnClickListener(){
                    int year = mDatePicker.getYear();
                    int month = mDatePicker.getMonth();
                    int day = mDatePicker.getDayOfMonth();
                    Date date = new GregorianCalendar(year,month,day).getTime();
                    sendResult(Activity.RESULT_OK,date);
                }
        	);
    }
}
```

`CrimeFragment`对返回的数据做出响应：

```java
public class CrimeFragment extends Fragment {
    // ...
    @Override public void onActivityResult(int requestCode,int resultCode,Intent data){
        if(resultCode != Activity.RESULT_OK){
            return;
        }
        if(requestCode == REQUEST_DATE){
            Date date == (Date) data.getSerializableExtra(DatePickerFragment.EXTRA_DATE);
            mCrime.setDate(date);
            mDateButton.setText(mCrime.getDate().toString());
        }
    }
}
```

### §1.2.9 菜单栏

`AppCompat`自带各种主题，可在`AndroidManifest.xml`设置：

```xml
<manifest>
	<application
        android:allowBackup="true"
        android:icon="@mipmap/ic_launcher"
        android:label="@string/app_name"
        android:roundIcon="@mipmap/ic_launcher_round"
        android:supportsRtl="true"
        android:theme="@style/Theme.CriminalIntent">
    <!-- ... -->
    </application>
</manifest>
```

现在我们使用的是`@style/Theme.CriminalIntent`自定义主题，该XML文件一般如下所示：

```XML
<resources xmlns:tools="http://schemas.android.com/tools">
    <!-- Base application theme. -->
    <style name="Theme.CriminalIntent" parent="Theme.MaterialComponents.DayNight.DarkActionBar">
        <!-- Primary brand color. -->
        <item name="colorPrimary">@color/purple_500</item>
        <item name="colorPrimaryVariant">@color/purple_700</item>
        <item name="colorOnPrimary">@color/white</item>
        <!-- Secondary brand color. -->
        <item name="colorSecondary">@color/teal_200</item>
        <item name="colorSecondaryVariant">@color/teal_700</item>
        <item name="colorOnSecondary">@color/black</item>
        <!-- Status bar color. -->
        <item name="android:statusBarColor" tools:targetApi="l">?attr/colorPrimaryVariant</item>
        <!-- Customize your theme here. -->
    </style>
</resources>
```

可以看到该样式继承于`Theme.MaterialComponents.DayNight.DarkActionBar`，我们将其修改为`Theme.AppCompat.Light.DarkActionBar`。

添加字符串资源：

```xml
<resources>
	<!-- ... -->
    <string name="new_crime">新建罪行</string>
    <string name="show_subtitle">显示详情</string>
    <string name="hide_subtitle">隐藏详情</string>
</resources>
```

菜单是一种类似于布局的资源，定义并保存在`res/menu`目录下。这里我们新建一个菜单XML布局文件`fragment_crime_list.xml`：

```xml
<menu xmlns:android="http://schemas.android.com/apk/res/android"
    xmlns:app="http://schemas.android.com/apk/res-auto">
    <item
        android:id="@+id/new_crime"
        android:icon="@android:drawable/ic_menu_add"
        android:title="@string/new_crime"
        app:showAsAction="ifRoom|withText"/>
    <!--app:showAsAction指定该选项在菜单中的位置
		always:永远显示在菜单栏上
		never:永远隐藏在折叠菜单中
		ifRoom:如果有空间的话就显示在菜单上
		withText:若空间足够就显示文字,如空间不够就显示图标
</menu>
```

这里我们使用的图标不是项目资源图标，而是系统图标。在Android SDK中，这些系统图标存储在目录`%AndroidSDKInstallPath%\platforms\android-%APILevel%\data\res\drawable-%Resolution%`中。

事实上，Android Studio内置了Configure Image Asset的功能，右键`res/drawable` ，在弹出的菜单中选择`New->Image Asset`，就能方便地从系统图标创建不同分辨率的项目资源图表。

实例化菜单：

```java
public class CrimeListFragment extends Fragment {
    // ...
    @Override public void onCreate(Bundle savedInstanceState){
        super.onCreate(savedInstanceState);
        setHasOptionsMenu(true);
    }
    @Override public void onCreateOptionsMenu(Menu menu,MenuInflater inflater){
        super.onCreateOptionsMenu(menu,inflater);
        inflater.inflate(R.menu.fragment_crime_list,menu);
    }
    // ...
}
```

实现新建罪行的功能：

```java
public class CrimeLab{
    // ...
    public void addCrime(Crime crime){
        mCrimes.add(crime);
    }
    // ...
    private CrimeLab(Context context){
        mCrimes = new ArrayList<>();
        // testCrimeLab();
    }
    // ...
    /* 取消测试生成的数据集
    public void testCrimeLab(){
        for(int i=0;i<1--;i++){
            Crime crime = new Crime();
            crime.setTitle("Crime #" + i);
            crime.setSolved(i % 2 == 0);
            mCrimes.add(crime);
        }
    }
    */
}
```

```java
public class CrimeListFragment extends Fragment {
    // ...
    @Override public boolean onOptionsItemSelected(MenuItem item){
        switch (item.getItemId()){
            case R.id.new_crime:
                Crime crime = new Crime();
                CrimeLab.get(getActivity()).addCrime(crime);
                Intent intent = CrimePagerActivity.newIntent(getActivity(),crime.getId());
                startActivity(intent);
                return true;
            default:
                return super.onOptionsItemSelected(item);
        }
    }
    // ...
}
```

启用后退按钮：

```xml
<!-- AndroidManifest.xml -->
<manifest>
	<application>
        <!-- ... -->
    	<activity
                  android:name=".CrimePagerActivity"
                  android:parentActivityName=".CrimeListActivity"/>
    </application>
</manifest>
```

更改菜单布局，添加显示/隐藏子标题的选项：

```xml
<menu>
	<!-- ... -->
    <item
          android:id="@+id/show_subtitle"
          android:title="@string/show_subtitle"
          app:showAsAction="ifRoom"/>
</menu>
```

设置工具栏子标题：

```java
public class CrimeListFragment extends Fragment {
    // ...
    private boolean mSubtitleVisible;
    @Override public View onCreateView(LayoutInflater inflater,ViewGroup container,Bundle savedInstanceState){
        // ...
        updateSubtitle(); // 否则新建Crime后子标题的Crime总数不变
    	return view;
    }
    @Override public void onResume(){
        // ...
        updateSubtitle(); // 否则新建Crime后子标题的Crime总数不变
    }
    @Override public void onCreateOptionsMenu(Menu menu,MenuInflater inflater){
        super.onCreateOptionsMenu(menu,inflater);
        inflater.inflate(R.menu.fragment_crime_list,menu);
        MenuItem subtitleItem = menu.findItem(R.id.show_subtitle);
        if(mSubtitleItem){
            subtitleItem.setTitle(R.string.hide_subtitle);
        }else{
            subtitleItem.setTitle(R.string.show_subtitle);
        }
    }
    @Override public boolean onOptionsItemSelected(MenuItem item){
        switch (item.getItemId()){
            case R.id.new_crime:
                // ...
            case R.id.show_subtitle:
                updateSubtitle();
                mSubtitleVisible = !mSubtitleVisible;
                getActivity().invalidateOptionsMenu();
                return true;
            default:
                // ...
        }
    }
    private void updateSubtitle(){
        CrimeLab crimelab = CrimeLab.get(getActivity());
        int crimeCount = crimeLab.getCrimes().size();
        Strign subtitle = getString(R.string.subtitle_format,crimeCount);
        AppCompatActivity activity = (AppCompatActivity) getActivity();
        activity.getSupportActionBar().setSubtitle(subtitle);
    }
    // ...
}
```

`getString(int resId,Object... formatArgs)`方法接受字符串资源中占位符的替换值，生成子标题字符串。

解决旋转屏幕造成子标题消失：

```java
public class CrimeListFragment extends Fragment {
    // ...
    private static final String SAVED_SUBTITLE_VISIBLE = "subtitle";
    // ...
    @Override public View onCreateView(LayoutInflater inflater,ViewGroup container,Bundle savedInstanceState){
        // ...
        if(savedInstanceState != null){
            mSubtitleVisible = savedInstanceState.getBoolean(SAVED_SUBTITLE_VISIBLE);
        }
        updateUI();
        updateSubtitle();
        return view;
    }
    // ...
    @Override public void onSaveInstanceState(Bundle outState){
        super.onSavedInstanceState(outState);
        outState.putBoolean(SAVED_SUBTITLE_VISIBL,mSubtitleVisible);
    }
    // ...
}
```

### §1.2.10 SQLite

新建`CrimeDbSchema`类和`CrimeBaseHelper`类，用于创建数据库模型：

```java
public class CrimeDbSchema {
    public static final class CrimeTable{
        public static final String NAME = "crimes";

        public static final class Columns{
            public static final String UUID = "uuid";
            public static final String TITLE = "title";
            public static final String DATE = "date";
            public static final String SOLVED = "solved";
        }
    }
}
```

```java
public class CrimeBaseHelper extends SQLiteOpenHelper {
    private static final int VERSION = 1;
    private static final String DATABASE_NAME = "crimeBase.db";

    public CrimeBaseHelper(Context context){
        super(context,DATABASE_NAME,null,VERSION);
    }
    @Override public void onCreate(SQLiteDatabase db) {

    }
    @Override
    public void onUpgrade(SQLiteDatabase db, int oldVersion, int newVersion) {

    }
}
```

在模型层添加SQLite调用：

```java
public class CrimeLab{
    // ...
    private Context mContext;
    private SQLiteDatabase mDatabase;
	// ...
    pribate CrimeLab(Context context){
        mContext = context.getApplicationContext();
        mDatebase = new CrimeBaseHelper(mContext).getWritableDatabase();
    }
}
```

```mermaid
graph TB
	context-->CrimeLabBuildingMethod2
	subgraph CrimeLab
		subgraph CrimeLabInstanceVariable ["实例变量"]
			mCrimes["private List&lt;Crime&gt; mCrimes"]
			mContext["private Context mContext"]
			mDatabase["private SQLiteDatabase mDatabase"]
		end
		subgraph CrimeLabBuildingMethod
			mCrimes-->CrimeLabBuildingMethod1["mCrimes=new ArrayList&lt;&gt;()"]
			mContext-->CrimeLabBuildingMethod2["mContext=context.getApplicationContext()"]
			CrimeLabBuildingMethod1-->CrimeLabBuildingMethod2-->CrimeLabBuildingMethod3["mDataBase=new CrimeBaseHelper(mContext).getWritableDatabase()"]
		end
	end
	subgraph CrimeBaseHelper extends SQLiteOpenHelper
		subgraph CrimeBaseHelperInstanceVariable
			
		end
		subgraph CrimeBaseHelperBuildingMethod
			
		end
	end
```

创建数据库时引入数据库名称常量，避免多次重复这么长的索引路径：

```java
import static com.example.criminalintent.CrimeDbSchema.CrimeTable;
public class CrimeBaseHelper extends SQLiteOpenHelper{
    // ...
    @Override public void onCreate(SQLiteDatabase db){
     // db.execSQL("create table " + CrimeDbSchema.CrimeTable.NAME);
        String command = "create table " + CrimeTable.NAME +
                "( _id integer primary key autoincrement, " +
                CrimeTable.Columns.UUID + ", " +
                CrimeTable.Columns.TITLE + ", " +
                CrimeTable.Columns.DATE + ", " +
                CrimeTable.Columns.SOLVED + ")";
        db.execSQL(command);
    }
    // ...
}
```

数据库文件将会被储存在`/data/data/com.example.criminalintent/databases`目录下。

出于节省内存的目的，我们再次更改模型层`CrimeLab`，删除其中的`List<Crime> mCrimes`实例，转而只使用`SQLiteDatabase mDatabase`实例：

```java
public class CrimeLab {
    // ...
    // private List<Crime> mCrimes;
    // ...
    private CrimeLab(Context context){
        mContext = context.getApplicationContext();
        mDatabase = new CrimeBaseHelper(mContext).getWritableDatabase();
        // mCrimes = new ArrayList<>();
    }
    public void addCrime(Crime C){
        // TODO
    }
    public void updateCrime(Crime crime){
        String uuidString = crime.getId().toString();
        ContentValues values = getContentValues(crime);
        mDatabase.update(
            CrimeDbSchema.CrimeTable.NAME,
            values,
            CrimeDbSchema.CrimeTable.Columns.UUID + " = ?",
            new String[] {uuidString}
        );
    }
    public List<Crime> getCrimes(){
        // TODO
        return new ArrayList<>();
    }
    public Crime getCrime(UUID id){
        // TODO
        return null;
    }
    private static ContentValues getContentValues(Crime crime){
        ContentValues values = new ContentValues();
        values.put(CrimeDbSchema.CrimeTable.Columns.UUID,crime.getId().toString());
        values.put(CrimeDbSchema.CrimeTable.Columns.TITLE,crime.getTitle());
        values.put(CrimeDbSchema.CrimeTable.Columns.DATE,crime.getDate().getTime());
        values.put(CrimeDbSchema.CrimeTable.Columns.SOLVED,crime.isSolved()?1:0);
        return values;
    }
    private Cursor queryCrimes(String whereClause,String[] whereArgs){
        Cursor cursor = mDatabase.query(
            CrimeDbSchema.CrimeTable.NAME,
            null, // 选择所有列
            whereClause,
            whereArgs,
            null, // groupBy
            null, // having
            null // orderBy
        );
        return cursor;
    }
}
```

- 增：`Long SQLiteDatabase.insert(String table,String nullColumnHack,ContentValues values)`，返回新插入行的ID

  - `String table`：指定数据库名称
  - `String nullColumnHack`：`values`中缺失了`table`中指定的名为`nullColumnHack`的列的数据，则传入`null`值
  - `ContentValues values`：单行数据集，通过`ContentValues.put(Key,Value)`以创建键值对

- 查：`Cursor SQLiteDatabase.query(String table,String[] columns,String where,String[] whereArgs,String groupBy,String having,String orderby,String limit)`，返回一个存储查询结果的`Cursor`实例

  - `String table`：指定数据库的名称
  - `String[] columns`：要返回的列，`null`代表返回全部列
  - `String where`：where子句的格式化字符串
  - `String[] whereArgs`：where子句的参数列表
  - `String groupBy`：groupBy子句
  - `String having`：having子句
  - `String orderBy`：orderBy子句
  - `String limit`：limit子句

- 改：`int SQLiteDatabase.update(String table,ContentValues values,String whereClause,String[] whereArgs)`，返回更新了多少行

  - `String table`：指定数据库名称
  - `ContentValues values`：更新完成后预期的单行数据集
  - `String whereClause`：指定where子句格式化字符串用于筛选
  - `String[] whereArgs`：`whereClause`格式化字符串的参数表

  > 注意：如果将`whereArgs`的参数直接放入`whereClause`子句中进行构造的话，就会引起SQL注入的风险，而使用`whereArgs`能100%规避这种风险。

`Cursor`是Android自带的数据处理类，定义于`android.database`包中。不假思索地，我们可以写出如下代码从搜索结果`Cursor`中得到所需键值对：

```java
String uuidString = cursor.getString(cursor.getColumnIndex(CrimeTable.Columns.UUID));
String title = cursor.getString(cursor.get)
long date = cursor.getLong(cursor.getColumnIndex(CrimeTable.Columns.DATE));
int isSolved = cursor.getInt(cursor.getColumnIndex(CrimeTable.Columns.SOLVED));
```

这种方法非常的麻烦，在此我们选择`CursorWrapper`类来管理`Cursor`实例：

```java
public class CrimeCursorWrapper extends CursorWrapper{
    public CrimeCursorWrapper(Cursor cursor){
        super(cursor);
    }
    public Crime getCrime(){
        String uuidString = getString(getColumnIndex(CrimeDbSchema.CrimeTable.Columns.UUID));
        String title = getString(getColumnIndex(CrimeDbSchema.CrimeTable.Columns.TITLE));
        long date = getLong(getColumnIndex(CrimeDbSchema.CrimeTable.Columns.DATE));
        int isSolved = getInt(getColumnIndex(CrimeDbSchema.CrimeTable.Columns.SOLVED));
        
        Crime crime = new Crime(UUID.fromString(uuidString));
        crime.setTitle(title);
        crime.setDate(new Date(date));
        crime.setSolved(isSolved != 0);
        
        return crime;
    }
}
```

退出编辑页面时更新数据库：

```java
public class CrimeFragment extends Fragment {
    // ...
    @Override public void onPause(){
        super.onPause();
        Crimelab.get(getActivity()).updateCrime(mCrime);
    }
    // ...
}
```

重载`Crime`构造方法，便于从数据库中创建之前保存过的`Crime`实例：

```java
public class Crime{
    // ...
    public Crime(){
        mId = UUID.randomUUID();
        mDate = new Date();
    }
    public Crime(UUID id){
        mId = id;
        mDate = new Date();
    }
    // ...
}
```

更新用于查询结果的函数：

```java
public class CrimeLab {
    // ...
    public List<Crime> getCrimes(){
        List<Crime> crimes = new ArrayList<>();
        CrimeCursorWrapper cursorWrapper = queryCrimes(null,null);
        try{
            cursorWrapper.moveToFirst();
            while(!cursorWrapper.isAfterLast()){
                crimes.add(cursorWrapper.getCrime());
                cursorWrapper.moveToNext();
            }
        }finally {
            cursorWrapper.close();
        }
        // return mCrimes;
        return crimes;
    }
    public Crime getCrime(UUID id){
        CrimeCursorWrapper cursorWrapper = queryCrimes(
            CrimeDbSchema.CrimeTable.Columns.UUID + " = ?",
            new String[]{id.toString()}
        );
        try {
            if(cursorWrapper.getCount() == 0){
                return null;
            }
            cursorWrapper.moveToFirst();
            return cursorWrapper.getCrime();
        }finally {
            cursorWrapper.close();
        }
        /*
        for(Crime crime : mCrimes){
            if (crime.getId().equals(id)){
                return crime;
            }
        }
        return null;
    	*/
    }
    // ...
    /*
    private Cursor queryCrimes(String whereClause,String[] whereArgs){
        // ...
    }
    */
    private CrimeCursorWrapper queryCrimes(String whereClause,String[] whereArgs){
        Cursor cursor = mDatabase.query(
                CrimeDbSchema.CrimeTable.NAME,
                null, // 选择所有列
                whereClause,
                whereArgs,
                null,
                null,
                null
        );
        return new CrimeCursorWrapper(cursor);
    }
}
```

最后将详情页的数据同步到列表页：

```java
public class CrimeListFragment extends Fragment {
    // ...
    private class CrimeAdapter extends RecyclerView.Adapter<CrimeHolder>{
        // ...
        public void setCrimes(List<Crime> crimes){
            mCrimes = crimes; // 实时更新
        }
    }
    private void updateUI(){
        // ...
        if(mAdapter == null){
            // ...
        }else{
            mAdapter.setCrimes(crimes); // 调用用于实时更新的方法
            mAdapter.notifyDataSetChanged();
        }
    }
}
```

### §1.2.11 隐式`Intent`

Android允许利用隐式`Intent`的方法实现从当前应用的`Activity`启动到另一个功能的`Activity`。在该项目中我们要实现分享到其他应用的功能。

添加两个分享按钮：

```xml
<!-- strings.xml -->
<resources>
	<!-- ... -->
    <string name="crime_suspect_text">选择嫌疑人</string>
    <string name="crime_report_text">分享到信息</string>
    <string name="crime_report">%1$s! 该罪行于%2$s %3$s %4$s</string>
    <string name="crime_report_solved">该举报已被解决</string>
    <string name="crime_report_unsolved">该举报未被解决</string>
    <string name="crime_report_no_suspect">未添加嫌疑人</string>
    <string name="crime_report_suspect">嫌疑人为%s</string>
    <string name="crime_report_subject">CriminalIntent Crime Report</string>
    <string name="send_report">通过…发送报告</string>
</resources>
```

```xml
<!-- fragment_crime.xml -->
<LinearLayout>
	<!-- ... -->
    <Button
        android:layout_width="match_parent"
        android:layout_height="wrap_content"
        android:id="@+id/crime_suspect"
        android:text="@string/crime_suspect_text"/>
    <Button
        android:layout_width="match_parent"
        android:layout_height="wrap_content"
        android:id="@+id/crime_report"
        android:text="@string/crime_report_text"/>
</LinearLayout>
```

更改模型层：

```java
public class Crime{
    // ...
    private String mSuspect;
    // ...
    public String getSuspect(){
        return mSuspect;
    }
    public void setSuspect(String suspect){
        mSuspect = suspect;
    }
}
```

```java
public class CrimeLab{
    // ...
    private static ContentValues getContentValues(Crime crime){
        // ...
        values.put(CrimeDbSchema.CrimeTable.Columns.SUSPECT,crime.getSuspect());
    	return values;
    }
    // ...
}
```

```java
public class CrimeCursorWrapper extends CursorWrapper{
    // ...
    public Crime getCrime(){
        // ...
        String suspect = getString(getColumnIndex(CrimeDbSchema.CrimeTable.Columns.SUSPECT));
    	//...
        crime.setSuspect(suspect);
        
    }
}
```

在数据库中添加字段：

```java
pubic class CrimeDbSchema{
    public static final class CrimeTable{
        public static final String NAME = "crimes";
        public static final class Columns{
            // ...
            public static final String SUSPECT = "suspect";
        }
    }
}
```

```java
public class CrimeBaseHelper extends SQLiteOpenHelper{
    // ...
    @Override public void onCreate(SQLiteDatabase db){
        String command = //...
            // ...
            CrimeTable.Columns.Suspect + ")";
        db.execSQL(command);
    }
    // ...
}
```

添加方法：

```java
public class CrimeFragment extends Fragment{
    // ...
    private String getCrimeReport(){
        String solvedString = null;
        if (mCrime.isSolved()) {
            solvedString = getString(R.string.crime_report_solved);
        } else {
            solvedString = getString(R.string.crime_report_unsolved);
        }
        String dateFormat = "EEE, MMM dd";
        String dateString = DateFormat.format(dateFormat, mCrime.getDate()).toString();
        String suspect = mCrime.getSuspect();
        if (suspect==null){
            suspect = getString(R.string.crime_report_no_suspect);
        }else {
            suspect = getString(R.string.crime_report_suspect);
        }
        String report = getString(R.string.crime_report,mCrime.getTitle(),dateString,solvedString,suspect);
        return report;
    }
    // ...
}
```

之前我们多次利用显式`Intent`实现跳转，其语法大致如下所示：

```java
Intent intent = new Intent(getActivity(),CrimePagerActivity.class);
intent.putExtra(EXTRA_CRIME_ID,crimeId);
startActivity(intent);
```

由此可见显式`Intent`结构非常的简单，相比之下隐式`Intent`就比较复杂了，它的组成部分有：

- 要执行的操作

  通常以`Intent`类中定义的类常量来表示，详见[Android SDK 开发者文档](https://developer.android.com/reference/android/content/Intent#summary)

- 待访问数据的位置

  例如URL，文件路径等

- 操作涉及的数据类型

  用[MINE形式](https://en.wikipedia.org/wiki/Media_type)指代数据类型，由互联网号码分配机构（IANA）负责[公示和更新](https://en.wikipedia.org/wiki/Media_type)

- 可选类别

  描述操作的具体启动方式，详见[`Android SDK 开发者文档`](https://developer.android.com/reference/android/content/Intent#CATEGORY_APP_BROWSER)

可以在`AndroidManifest.xml`中声明此应用的某一个`Activity`能够执行的操作：

```xml
<activity
          android:name=".BrowserActivity"
          android:label="@string/xxx">
	<intent-filter>
    	<action android:name="android.intent.action.VIEW"/>
        <category android:name="android.intent.category.DEFAULT"/>
        <data android:scheme="http"
              android:host="www.google.com"/>
    </intent-filter>
</activity>
```

添加创建隐式`Intent`的方法：

```java
public class CrimeFragment extends Fragment {
    // ...
    private Button mReportButton;
    // ...
    @Override public View onCreateView(LayoutInflater inflater,ViewGroup container,Bundle savedInstanceState){
        // ...
        mReportButton = (Button) v.findViewById(R.id.crime_report);
        mReportButton.setOnClickListener(new View.OnClickListener() {
            @Override public void onClick(View v) {
                Intent intent = new Intent(Intent.ACTION_SEND);
                intent.setType("text/plain");
                intent.putExtra(Intent.EXTRA_TEXT,getCrimeReport());
                intent.putExtra(Intent.EXTRA_SUBJECT,getString(R.string.crime_report_subject));
                startActivity(intent);
            }
        });
    }
    // ...
}
```

用户在选择发送方式时可能会"选择默认应用"，如果要强制让用户每次都选择应用列表的话，可以使用选择器：

```java
Intent intnet = new Intent(Intent.ACTION_SEND);
// ...
intent = Intent.createChooser(intent,getString(R.string.send_report));
startActivity(intent);
```

接着创建另一个隐式`Intent`用于获取联系人信息：

```java
public class CrimeFragment extends Fragment{
    // ...
    private Button mSuspectButton;
	// ...
    private static final int REQUEST_CONTACT = 1;
    // ...
	@Override public View onCreateView(LayoutInflater inflater,ViewGroup container,Bundle savedInstanceState){
        // ...
        final Intent pickContact = new Intent(Intent.ACTION_PICK, ContactsContract.Contacts.CONTENT_URI);
        mSuspectButton = (Button) v.findViewById(R.id.crime_suspect);
        mSuspectButton.setOnClickListener(new View.OnClickListener() {
            @Override public void onClick(View v) {
                startActivityForResult(pickContact,REQUEST_CONTACT);
            }
        });
        return v;
    }
}
```

为了处理联系人信息，Android SDK的[`ContentProvider`](developer.android.com/guide/topics/providers/contacts-provider.html)类提供了一系列API用于封装联系人数据并给其他应用使用，我们需要通过`ContentResolver`来访问`ContentProvider`：

```java
public class CrimeFragment extends Fragment{
    // ...
    @Override public void onActivityResult(int requestCode,int resultCode,Intent data){
        if(resultCode != Activity.RESULT_OK){
            return;
        }
        if(requestCode == REQUEST_DATE){
            Date date = (Date) data.getSerializableExtra(DataPickerFragment.EXTRA_DATE);
            mCrime.setDate(date);
            updateDate();
        }else if(requestCode == REQUEST.CONTACT && data != null){
            Uri contactUri = data.getData();
            String[] queryFields = new String[]{
                    ContactsContract.Contacts.DISPLAY_NAME
            };
            Cursor cursor = getActivity().getContentResolver().query(
                    contactUri,
                    queryFields,
                    null,
                    null,
                    null
            );
            try {
                if (cursor.getCount() == 0){
                    return;
                }
                cursor.moveToFirst();
                String suspect = cursor.getString(0);
                mCrime.setSuspect(suspect);
                mSuspectButton.setText(suspect);
            }finally {
                cursor.close();
            }
        }
    }
    // ...
}
```

如果手机上没有与联系人相关的应用，那么APP就找不到匹配的`Activity`，应用就会崩毁。为了避免这个问题，首先使用`PackageManager`类进行自检：

```java
public class CrimeFragment extends Fragment{
    // ...
    @Override public View onCreateView(LayoutInflater inflater, ViewGroup container,Bundle savedInstanceState){
        // ...
        PackageManager packageManager = getActivity().getPackageManager();
        if(packageManager.resolveActivity(pickContact,PackageManager.MATCH_DEFAULT_ONLY)==null){
            mSuspectButton.setEnabled(false);
        }
        return v;
    }
    // ...
}
```



## §1.5 Locatr

Android原生提供了一些列基本地理位置的API，定义于`android.location`库中。过去，为获得定位数据，必须严格手动调用GPS、基站、Wifi、加速感应器、陀螺仪等一系列API。为解决上述问题，Google Play Service提供了Fused Location Provider的定位服务。

### §1.5.1 搭建框架

建立模版XML文件`activity_fragment.xml`和抽象类`SingleFragmentActivity`：

```xml
<!-- 用于容纳Fragment -->
<FrameLayout android:id="@+id/fragment_container"
    xmlns:android="http://schemas.android.com/apk/res/android"
    android:layout_width="match_parent"
    android:layout_height="match_parent">
</FrameLayout>
```

```java
package com.example.photogallery;
import android.os.Bundle;
import androidx.appcompat.app.AppCompatActivity;
import androidx.fragment.app.Fragment;
import androidx.fragment.app.FragmentManager;

public abstract class SingleFragmentActivity extends AppCompatActivity {
    protected abstract Fragment createFragment();
    @Override protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        // 将SingleFragmentActivity的子类的视图设置为activity_fragment.xml(只有一个<FrameLayout>根节点)
        setContentView(R.layout.activity_fragment);
		// 获取fragment所在父容器的管理器(FragmentManager)
        FragmentManager fm = getSupportFragmentManager();
        // 将id为fragment_container的根标签<FrameLayout>赋给fragment变量
        Fragment fragment = fm.findFragmentById(R.id.fragment_container);
		// 如果<FrameLayout>内没有任何内容
        if (fragment == null) {
            // 则刷新fragment为子类定义的createFragment()返回的Fragment,并将新fragment托给FragmentManager管理
            fragment = createFragment();
            fm.beginTransaction()
                    .add(R.id.fragment_container, fragment)
                    .commit();
        }
    }
}
```

创建`PhotoGalleryActivity`类，将其设定为`SingleFragmentActivity`的子类：

```java
package com.example.photogallery;
import androidx.appcompat.app.AppCompatActivity;

public class PhotoGalleryActivity extends SingleFragmentActivity {
    @Override Fragment createFragment(){
        return PhotoGalleryFragment.newInstance();
    }
}
```

新建`fragment_photo_gallery.xml`：

```xml
<?xml version="1.0" encoding="utf-8"?>
<androidx.recyclerview.widget.RecyclerView
    xmlns:android="http://schemas.android.com/apk/res/android"
    xmlns:tools="http://schemas.android.com/tools"
    android:layout_width="match_parent"
    android:layout_height="match_parent"
    android:id="@+id/photo_recycler_view"
    tools:context="com.example.photogallery.PhotoGalleryActivity">

</androidx.recyclerview.widget.RecyclerView>
```

新建`PhotoGalleryFragment.java`：

```java
package com.example.photogallery;

import android.os.Bundle;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import androidx.fragment.app.Fragment;
import androidx.recyclerview.widget.GridLayoutManager;
import androidx.recyclerview.widget.RecyclerView;

public class PhotoGalleryFragment extends Fragment {
    private RecyclerView mPhotoRecyclerView;
    public static PhotoGalleryFragment newInstance(){
        return new PhotoGalleryFragment();
    }
    @Override public void onCreate(Bundle savedInstanceState){
        super.onCreate(savedInstanceState);
        setRetainInstance(true);
    }
    @Override public View onCreateView(LayoutInflater inflater, ViewGroup container, Bundle savedInstanceState){
        View v = inflater.inflate(R.layout.fragment_photo_gallery,container,false);
        mPhotoRecyclerView = (RecyclerView) v.findViewById(R.id.photo_recycler_view);
        mPhotoRecyclerView.setLayoutManager(new GridLayoutManager(getActivity(),3));
        return v;
    }
}
```

此时的业务逻辑整体如下：

```mermaid
flowchart TB
	subgraph activity_fragment.xml [activity_fragment.xml]
		FrameLayout1["&lt;FrameLayout&gt<br>android:id=&quot;fragment_container&quot;"]
	end
	subgraph SingleFragmentActivity [SingleFragmentActivity]
		subgraph onCreateFuncOfSingleFragmentActivity ["onCreate()"]
            setContentView1["setContentView(R.layout.activity_fragment)"]
            setContentView1.->FrameLayout1
            FragmentManager1["FragmentManager fm = getSupportFragmentManager()"]
            FragmentManager1.->FrameLayout1
            setContentView1-->FragmentManager1
            FragmentManager1-->If1("fm.findFragmentById<br>(R.id.fragment_container)")
            If1--"不为Null"-->FragmentOfSingleFragmentActivity1["Fragment fragment = fm.findFragmentById<br/>(R.id.fragment_container)"]
            If1--"为Null"-->FragmentOfSingleFragmentActivity2["Fragment fragment = createFragment()"]
            FragmentOfSingleFragmentActivity2-->FragmentOfSingleFragmentActivity3["fm.beginTransction()<br>.add(R.id.fragment_container,fragment)<br>.commit()"]
            FragmentOfSingleFragmentActivity4[得到了fragment]
            FragmentOfSingleFragmentActivity1-->FragmentOfSingleFragmentActivity4
            FragmentOfSingleFragmentActivity3-->FragmentOfSingleFragmentActivity4
            FragmentOfSingleFragmentActivity3.->FrameLayout1
        end
	end
    subgraph PhotoGalleryActivity [PhotoGalleryActivity]
        subgraph createFragmentOfPhotoGalleryActivity [createFragment]
            createFragmentOfPhotoGalleryActivity1["返回PhotoGalleryFragment.newInstance()"]
        end
    end
	subgraph fragment_photo_gallery.xml [fragment_photo_gallery.xml]
        ViewPager1["androidx.recyclerview.widget.RecyclerView<br/>android:id=&quot;photo_recycler_view&quot;"]
    end
    subgraph PhotoGalleryFragment [PhotoGalleryFragment]
        subgraph newInstanceOfPhotoGalleryFragment ["newInstance()"]
            newInstanceOfPhotoGalleryFragment1["返回一个PhotoGalleryFragment实例"]
        end
        subgraph onCreateOfPhotoGalleryFragment ["onCreate()"]
            onCreateOfPhotoGalleryFragment1["setRetainInstance(true)<br>在Activity销毁后保留Fragment"]
        end
        subgraph onCreateViewOfPhotoGalleryFragment ["onCreateView()"]
            onCreateViewOfPhotoGalleryFragment1["View v = inflater.inflate(R.layout.fragment_photo_gallery,container,false)"]
            onCreateViewOfPhotoGalleryFragment2["mPhotoRecyclerView = (RecyclerView) v.findViewById(R.id.photo_recycler_view)"]
            onCreateViewOfPhotoGalleryFragment3["mPhotoRecyclerView.setLayoutManager(new GridLayoutManager(getActivity(),3))"]
            onCreateViewOfPhotoGalleryFragment4["返回View实例v"]
            onCreateViewOfPhotoGalleryFragment1-->onCreateViewOfPhotoGalleryFragment2
            onCreateViewOfPhotoGalleryFragment2-->onCreateViewOfPhotoGalleryFragment3
            onCreateViewOfPhotoGalleryFragment3-->onCreateViewOfPhotoGalleryFragment4
        end
        onCreateViewOfPhotoGalleryFragment1.->ViewPager1
        onCreateViewOfPhotoGalleryFragment2.->ViewPager1
        createFragmentOfPhotoGalleryActivity1-->newInstanceOfPhotoGalleryFragment1
    end
    SingleFragmentActivity--"延伸出子类"-->PhotoGalleryFragment
```

`SingleFramentActivity`作为超类，起到了模版的作用：

```mermaid
flowchart TB
	subgraph activity_fragment.xml [activity_fragment.xml]
		FrameLayout1["&lt;FrameLayout&gt<br>android:id=&quot;fragment_container&quot;"]
	end
	subgraph SingleFragmentActivity [SingleFragmentActivity]
		subgraph onCreateFuncOfSingleFragmentActivity ["onCreate()"]
            setContentView1["setContentView(R.layout.activity_fragment)"]
            setContentView1.->FrameLayout1
            FragmentManager1["FragmentManager fm = getSupportFragmentManager()"]
            FragmentManager1.->FrameLayout1
            setContentView1-->FragmentManager1
            FragmentManager1-->If1("fm.findFragmentById<br>(R.id.fragment_container)")
            If1--"不为Null"-->FragmentOfSingleFragmentActivity1["Fragment fragment = fm.findFragmentById<br/>(R.id.fragment_container)"]
            If1--"为Null"-->FragmentOfSingleFragmentActivity2["Fragment fragment = createFragment()"]
            FragmentOfSingleFragmentActivity2-->FragmentOfSingleFragmentActivity3["fm.beginTransction()<br>.add(R.id.fragment_container,fragment)<br>.commit()"]
            FragmentOfSingleFragmentActivity4[得到了fragment]
            FragmentOfSingleFragmentActivity1-->FragmentOfSingleFragmentActivity4
            FragmentOfSingleFragmentActivity3-->FragmentOfSingleFragmentActivity4
            FragmentOfSingleFragmentActivity3.->FrameLayout1
        end
	end
```

在`SingleFramentActivity`类的基础上延伸出了`PhotoGalleryActivity`类，其唯一作用就是通过`createFragment()`方法返回一个`PhotoGalleryFragment`实例：

```mermaid
graph LR
SingleFragmentActivity--"延伸出子类"-->PhotoGalleryActivity--"createFragment()"-->PhotoGalleryFragment
```

`PhotoGalleryActivity`的结构如下：

```mermaid
graph TB
    subgraph fragment_photo_gallery.xml [fragment_photo_gallery.xml]
        ViewPager1["androidx.recyclerview.widget.RecyclerView<br/>android:id=&quot;photo_recycler_view&quot;"]
    end
    subgraph PhotoGalleryFragment [PhotoGalleryFragment]
        subgraph newInstanceOfPhotoGalleryFragment ["newInstance()"]
            newInstanceOfPhotoGalleryFragment1["返回一个PhotoGalleryFragment实例"]
        end
        subgraph onCreateOfPhotoGalleryFragment ["onCreate()"]
            onCreateOfPhotoGalleryFragment1["setRetainInstance(true)<br>在Activity销毁后保留Fragment"]
        end
        subgraph onCreateViewOfPhotoGalleryFragment ["onCreateView()"]
            onCreateViewOfPhotoGalleryFragment1["View v =<br>inflater.inflate(R.layout.fragment_photo_gallery,container,false)"]
            onCreateViewOfPhotoGalleryFragment2["mPhotoRecyclerView = <br>(RecyclerView) v.findViewById(R.id.photo_recycler_view)"]
            onCreateViewOfPhotoGalleryFragment3["mPhotoRecyclerView.setLayoutManager<br>(new GridLayoutManager(getActivity(),3))"]
            onCreateViewOfPhotoGalleryFragment4["返回View实例v"]
            onCreateViewOfPhotoGalleryFragment1-->onCreateViewOfPhotoGalleryFragment2
            onCreateViewOfPhotoGalleryFragment2-->onCreateViewOfPhotoGalleryFragment3
            onCreateViewOfPhotoGalleryFragment3-->onCreateViewOfPhotoGalleryFragment4
        end
        onCreateViewOfPhotoGalleryFragment1.->ViewPager1
        onCreateViewOfPhotoGalleryFragment2.->ViewPager1
    end
```

创建`FlickrFetchr`类，用于获得Flickr网站上的图片：

```java
package com.example.photogallery;
import java.io.ByteArrayOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.net.HttpURLConnection;
import java.net.URL;

public class FlickrFetchr {
    public byte[] getUrlBytes(String urlSpec) throws IOException{
        URL url = new URL(urlSpec);
        HttpURLConnection connection = (HttpURLConnection) url.openConnection();
        try {
            //OutputStream--延伸出-->ByteArrayOutputStream
            ByteArrayOutputStream out = new ByteArrayOutputStream();
            InputStream in = connection.getInputStream();
            if(connection.getResponseCode() != HttpURLConnection.HTTP_OK){
                throw new IOException(connection.getResponseMessage()+": with "+urlSpec);
            }
            int bytesRead = 0;
            byte[] buffer = new byte[1024];
            while((bytesRead=in.read(buffer))>0){
                out.write(buffer,0,bytesRead);
            }
            out.close();
            return out.toByteArray();
        }finally {
            connection.disconnect();
        }
    }
    public String getUrlString(String urlSpec) throws IOException{
        return new String(getUrlBytes(urlSpec));
    }
}
```

然后在后台线程上调用该网络类：

```java
public class PhotoGalleryFragment extends Fragment {
    private static final String TAG = "PhotoGalleryFragment";
    // ...
    @Override public void onCreate(Bundle savedInstanceState){
        // ...
        new FetchItemsTask().execute();
    }
    private class FetchItemsTask extends AsyncTask<Void,Void,Void>{
        @Override protected void doInBackground(Void... params){
            try{
                String result = new FilckrFetchr().getUrlString("https://bignerdranch")
            	Log.i(TAG,"Fetched contents of URL:" + result);
            }catch(IOException ioe){
                Log.e(TAG,"Failed to fetch URL:"+ioe);
            }
            return null;
        }
    }
}
```

```mermaid
flowchart TB
	Input1[/输入URL/]
    subgraph FlickrFetchr ["FlickrFetchr"]
        subgraph getUrlString["getUrlString(String urlSpec)"]
            getUrlString1["返回(String) getUrlBytes(String urlSpec)"]
        end 
    end
    Input1-->getUrlString1
    getUrlString1-->FlickrFetchr1
    subgraph PhotoGalleryFragment [PhotoGalleryFragment]
        subgraph newInstanceOfPhotoGalleryFragment ["newInstance()"]
            newInstanceOfPhotoGalleryFragment1["返回一个PhotoGalleryFragment实例"]
        end
        newInstanceOfPhotoGalleryFragment-->onCreateOfPhotoGalleryFragment
        subgraph onCreateOfPhotoGalleryFragment ["onCreate()"]
            onCreateOfPhotoGalleryFragment1["setRetainInstance(true)<br>在Activity销毁后保留Fragment"]
            onCreateOfPhotoGalleryFragment2["new FetchItemsTask().execute();"]
        end
        subgraph FetchItemsTask
            subgraph doInBackground
                doInBackground1["String result = new FilckrFetchr()<br>.getUrlString(&quot;https://www.bignerdranch.com&quot;)"]
            end
        end
        onCreateOfPhotoGalleryFragment2-->doInBackground1-->Input1
    end
    subgraph FlickrFetchr ["FlickrFetchr"]
        FlickrFetchr1["URL url = new URL(urlSpec)"]
        FlickrFetchr2["HttpURLConnection connection = <br>(HttpURLConnection)url.openConnection()"]
        FlickrFetchr3["InputStream in = connection.getInputStream()"]
        FlickrFetchr4{connection<br>.getResponseCode}
        FlickrFetchr5["throw IOExpection()"]
        FlickrFetchr6["byte[] buffer = new byte[1024]"]
        FlickrFetchr7["out.write(buffer,0,bytesRead)<br>out.write(buffer,0,bytesRead)<br>out.write(buffer,0,bytesRead)<br>...<br>out.close()"]
        FlickrFetchr8["conntection.disconnect()"]
        FlickrFetchr9[/"返回out.toByteArray()"/]
        FlickrFetchr1-->FlickrFetchr2
        FlickrFetchr2-->FlickrFetchr3
        FlickrFetchr3-->FlickrFetchr4
        FlickrFetchr4--"非200"-->FlickrFetchr5
        FlickrFetchr4--"200"-->FlickrFetchr6
        FlickrFetchr6-->FlickrFetchr7
        FlickrFetchr7-->FlickrFetchr8
    FlickrFetchr8-->FlickrFetchr9
    end
    FlickrFetchr9--"String转换"-->doInBackground1
```

### §1.5.2 API

申请API_KEY并添加API调用代码：

```java
public class FlickrFetchr {
    private static final String API_KEY = "xxxxx";
    private static final String API_PASSWORD = "xxxxx";
    private static final String TAG = "FlickrFetchr";
    public void fetchItems(){
        try {
            String url = Uri.parse("https://api.flickr.com/services/rest/")
                    .buildUpon()
                    .appendQueryParameter("method","flickr.photos.getRecent")
                    .appendQueryParameter("api_key",API_KEY)
                    .appendQueryParameter("format","json")
                    .appendQueryParameter("nojsoncallback","1")
                    .appendQueryParameter("extras","url_s")
                    .build().toString();
            String jsonString = getUrlString(url);
            Log.i(TAG,"Received JSON: " + jsonString);
        }catch (IOException ioException){
            Log.e(TAG,"Failed to fetch items",ioException);
        }
    }
    // ...
}
```

```java
public class PhotoGalleryFragment extends Fragment{
    // ...
    private class FetchItemsTask extends AsyncTask<Void,Void,Void>{
        @Override protected Void doInBackground(Void... params){
			new FlickrFetchr().fetchItems();
            return null;
        }
    }
    // ...
}
```

### §1.5.3 线程与主线程

一般线程中的代码会逐步执行，而Android主线程的代码处于一个无限循环中，不停的等待系统和用户触发APP监听的事件：

```mermaid
graph LR
subgraph 一般线程
	进程入口指针-->代码1[代码]-->代码2[...]-->代码3[代码]-->完成
end
subgraph 主线程
	subgraph &nbsp;
		监听器1[监听器]-->监听器2[监听器]-->监听器3[监听器]-->监听器1
	end
	触发事件1[触发事件].->监听器1
	触发事件2[触发事件].->监听器2
	触发事件3[触发事件].->监听器3
end
```

Android禁止任何主线程的网络连接行为，如果强行连接则会抛出`NetworkOnMainThreadException`异常。这是因为网络连接需要时间做出相应或下载文件。

### §1.5.4 解析JSON

创建一个模版类`GalleryItem`：

```java
public class GalleryItem {
    private String mCaption;
    private String mId;
    private String mUrl;
    @NonNull @Override public String toString(){
        return mCaption;
    }
    public String getCaption() {
        return mCaption;
    }
    public void setCaption(String caption) {
        mCaption = caption;
    }
    public String getUrl() {
        return mUrl;
    }
    public void setUrl(String url) {
        mUrl = url;
    }
    public String getId() {
        return mId;
    }
    public void setId(String id) {
        mId = id;
    }
}
```

我们使用的Flickr API返回的JSON格式如下：

```json
{
    "photos": {
        "page": 1,
        "pages": 10,
        "perpage": 100,
        "total": 1000,
        "photo": [
            {
                "id": "51844480537",
                "owner": "170905058@N08",
                "secret": "235c7ed69c",
                "server": "65535",
                "farm": 66,
                "title": "NZG_6053.jpg",
                "ispublic": 1,
                "isfriend": 0,
                "isfamily": 0
            },
            {
                "id": "51844480987",
                "owner": "10583065@N06",
                "secret": "e3d6ed8de4",
                "server": "65535",
                "farm": 66,
                "title": "Doorway to the Soul",
                "ispublic": 1,
                "isfriend": 0,
                "isfamily": 0
            }
        ]
    },
    "stat": "ok"
}
```

其层级树如下：

```mermaid
graph TB
	JSON[JSON]
	photos["&quot;photos&quot;"]
	stat["&quot;stat&quot;"]
	page["&quot;page&quot;"]
	pages["&quot;pages&quot;"]
	perpage["&quot;perpage&quot;"]
	total["&quot;total&quot;"]
	photo["&quot;photo&quot;"]
	id["&quot;id&quot;"]
	owner["&quot;owner&quot;"]
	secret["&quot;secret&quot;"]
	server["&quot;farm&quot;"]
	farm["&quot;farm&quot;"]
	title["&quot;title&quot;"]
	ispublic["&quot;ispublic&quot;"]
	isfriend["&quot;isfriend&quot;"]
	isfamily["&quot;isfamily&quot;"]
	JSON-->photos
	JSON-->stat
	subgraph "&nbsp;"
		photos-->page
		photos-->pages
		photos-->perpage
		photos-->total
		photos-->photo
		subgraph &nbsp;
			photo-->id
			photo-->owner
			photo-->secret
			photo-->server
			photo-->farm
			photo-->title
			photo-->ispublic
			photo-->isfriend
			photo-->isfamily
		end
	end

```

我们的解析思路如下：

```mermaid
graph TB
	JSON_FILE--"new JSONObject(jsonString)"-->JSONObject1["JSONObject<br>jsonBody"]
	--"getJSONObject(&qout;photos&qout;)"-->JSONObject2["JSONObject<br>photosJsonObject"]
	--"getJSONArray(&qout;photo&qout;)"-->JSONArray["JSONArray<br>photoJsonArray"]
	--"getJSONObject(index)"-->JSONObject3["JSONObject1<br>photoJsonObject"]
	JSONArray--"getJSONObject(index)"-->JSONObject4["JSONObject1<br>photoJsonObject"]
	JSONArray--"getJSONObject(index)"-->JSONObject5["JSONObject1<br>photoJsonObject"]
	JSONArray--"getJSONObject(index)"-->JSONObject6["."]
```

`json.org`库提供了一系列用于解析JSON的API，下面在`FlickrFetchr.java`中添加解析：

```java
public class FlickrFetchr{
    // ...
    public List<GalleryItem> fetchItems(){
        try{
            // ...
            JSONObjeR ct jsonBody = new JSONObject(jsonString);
            parseItems(items,jsonBody);
        }catch (IOException ioException){
            Log.e(TAG,"Failed to fetch items",ioException);
        }catch (JSONExcpetion jsonException){
            Log.e(TAG,"Failed to parse JSON");
        }
    }
    private void parseItems(List<GalleryItem> items, JSONObject jsonBody) throws IOException,JSONException{
        JSONObject photosJsonObject = jsonBody.getJSONObject("photos");
        JSONArray photoJsonArray = photosJsonObject.getJSONArray("photo");
        for (int i=0;i<photoJsonArray.length();i++){
            JSONObject photoJsonObject = photoJsonArray.getJSONObject(i);
            GalleryItem item = new GalleryItem();
            item.setId(photoJsonObject.getString("id"));
            item.setCaption(photoJsonObject.getString("title"));
            if(!photoJsonObject.has("url_s")){
                continue;
            }else{
                item.setUrl(photoJsonObject.getString("url_s"));
            }
            items.add(item);
        }
    }
    // ...
}
```

接下来设置`RecyclerView`：

```java
public class PhotoGalleryFragment extends Fragment {
    // ...
    private class PhotoHolder extends RecyclerView.ViewHolder{
        private TextView mTitleTextView;
        public PhotoHolder(View itemView){
            super(itemView);
            mTitleTextView = (TextView) itemView;
        }
        public void bindGalleryItem(GalleryItem item){
            mTitleTextView.setText(item.toString());
        }
    }
    private class PhotoAdapter extends RecyclerView.Adapter<PhotoHolder>{
        private List<GalleryItem> mGalleryItems;
        public PhotoAdapter(List<GalleryItem> galleryItems){
            mGalleryItems = galleryItems;
        }
        @Override public PhotoHolder onCreateViewHolder(ViewGroup viewGroup,int viewType){
            TextView textView = new TextView(getActivity());
            return new PhotoHolder(textView);
        }
        @Override public void onBindViewHolder(PhotoHolder photoHolder, int position) {
            GalleryItem galleryItem = mGalleryItems.get(position);
            photoHolder.bindGalleryItem(galleryItem);
        }
        @Override public int getItemCount(){
            return mGalleryItems.size();
        }
    }
	// ...   
}

```

```mermaid
graph TB
	galleryItems["List&lt;GalleryItem&gt; galleryItems<br>mItems为new ArrayList&lt;GalleryItem&gt;"]
	itemView["View itemView"]
	subgraph PhotoAdapter["RecyclerView.Adapterr<br>&rarr;PhotoAdapter"]
		subgraph onCreateViewHolder ["onCreateViewHolder()"]
			onCreateViewHolder1["return new PhotoHolder(new TextView(getActivity())"]
		end
		subgraph onBindViewHolder ["onBindViewHolder()"]
			onBindViewHolder1["GalleryItem galleryItem=mGalleryItems.get(position)"]
			onBindViewHolder2["photoHolder.bindGalleryItem(galleryItem)"]
			onBindViewHolder1-->onBindViewHolder2
		end
		subgraph getItemCount ["getItemCount()"]
			getItemCount1["return mGalleryItems.size()"]
		end
        subgraph onCreate ["onCreate()"]
            mGalleryItems
        end
	end
	subgraph PhotoHolder
		subgraph bindGalleryItem ["bindGalleryItem"]
			bindGalleryItem1["mTitleTextView.setText(item.toString())"]
		end
		subgraph PhotoHolderFunc ["PhotoHolder(View itemView)"]
			PhotoHolderFunc1["mTitleTextView=(TextView)itemView"]
		end
	end
    subgraph setupAdapter ["setupAdapter"]
        setupAdapter1{"isAdded()"}
        setupAdapter2["mPhotoRecyclerView.setAdapter<br>(new PhotoAdapter(mItems));"]
        setupAdapter1--true-->setupAdapter2
    end
	itemView.->PhotoHolderFunc1
    PhotoHolderFunc1.->onCreateViewHolder1
    onCreateViewHolder1.->onBindViewHolder1
    galleryItems.->mGalleryItems
    setupAdapter2.->galleryItems
```

```java
public class PhotoGalleryFragment extends Fragment{
    // ...
    private List<GalleryItem> mItems = new ArrayList<>();
    // ...
    @Override public View onCreateView(LayoutInflater inflater,ViewGroup container,Bundle savedInstanceState){
        // ...
        setupAdapter();
        // ...
    }
    // ...
    private void setupAdapter(){
        if(isAdded()){
            mPhotoRecyclerView.setAdapter(new PhotoAdapter(mItems));
        }
    }
    // ...
}
```

> 注意：`Fragment`类中定义了`isAdded()`方法，用于判断当前`fragment`实例是否与目标`activity`实例相关联。如果不关联的话，当前`fragment`实例调用的`TextView textView = new TextView(getActivity())`就会失败。

现在获得API返回的数据并解析后，就需要调用`setupAdapter()`，将解析后的`List`传给`PhotoAdapter`类的构造方法生成实例，在将该实例作为`mPhotoRecyclerView`的`Adapter`。那么在哪里调用`setupAdapter()`呢？如果在`doInBackground()`方法中调用的话，内存中的对象会互相踩踏使得APP崩溃。安全起见，Android不允许从后台线程更细UI。我们需要让负责网络的`FlickrFetchr().fetchItems()`和负责UI的`setupAdapter()`互不干扰，而`onPostExecute()`方法就能实现该功能。

`onPostExecute()`是主线程的方法，而且在`doInBackground()`执行完毕后才会运行：

```java
public class PhotoGalleryFragment extends Fragment {
    // ...
    /* 原方法
    private class FetchItemsTask extends AsyncTask<Void,Void,Void>{
        @Override protected Void doInBackground(Void... params) {
            new FlickrFetchr().fetchItems();
            return null;
        }
    }
    */
    private class FetchItemsTask extends AsyncTask<Void,Void,List<GalleryItem>> {
        @Override protected List<GalleryItem> doInBackground(Void... params){
            // 将List<GalleryItem>对象传给onPostExecute()
            return new FlickrFetchr().fetchItems();
        }
        @Override protected void onPostExecute(List<GalleryItem> items){
            mItems = items;
            setupAdapter();
        }
    }
}
```

### §1.5.5 清理`AsyncTask`

本例中，我们在创建`PhotoGalleryFragment`时设置了"不随`Activity`销毁"的选项：

```java
public class PhotoGalleryFragment extends Fragment{
    // ...
    @Override public void onCreate(Bundle savedInstanceState){
		// ...
        setRetainInstance(true);
        // ...
    }
    // ...
}
```

这种方式的好处是，当屏幕旋转使得原有`Activity`重启时，`Fragment`不会随之消失，自然不会重复触发`Fragment`中定义的`private class FetchItemsTask extends Async<Void,Void,List<GalleryItem>>`中调用的网络请求方法。

针对某些复杂场景，我们需要将`AsyncTask`实例赋值给其他实例变量，这样就可以在`onStop(...)`或`onDestroy(...)`中调用`AsyncTask.cancel(boolean)`来随时撤销运行中的`AsyncTask`实例了。`AsyncTask.cancel(boolean)`有以下两种工作模式：

- 温和的

  `AsyncTask.cancel(false)`只是将`isCancelled()`的状态设置为`true`，随后`AsyncTask`检查`isCancelled()`状态，如果为`true`则选择提前结束该实例的运行。

- 粗暴的

  `AsyncTask.cancel(true)`会立即终止`doInBackground(...)`方法所在的线程，应尽量避免这种做法。

### §1.5.6 `AsyncTask`泛型

`AsyncTask`的泛型包含三个参数：

- 第一个参数：要传给`AsyncTask.execute(...)`方法的实参类型

  ```java
  AsyncTask<String,Void,Void> task = new AsyncTask<String,Void,Void>(){
      public Void doInBackground(String... params){
          for(String param : params){
              Log.i("Received message:",param);
          }
      }
  }
  task.execute("hello","world","!");
  ```

- 第二个参数：发送进度更新需要的类型

  ```java
  final ProgressBar progressBar = /* certain ProgressBar Object */ ;
  final int ProgressBarMax = /* maximum of the ProgressBar Object */ ;
  progressBar.setMax(ProgressBarMax);
  AsyncTask<Void,Integer,Void> trackProgess = new AsyncTask<Void,Integer,Void>(){
      @Override protected Void doInBackground(Void... params){
          while(!isfinsished()){
              publishProgress(getProgress()); // AsyncTask.java中已定义publishProgress()
          }
      }
      @Override protected void onProgressUpdate(Integer... params){
          int progress = params[0];
          trackProgress.setProgress(progress); // AsyncTask.java中已定义setProgress()
      }
  }
  trackProgress.execute();
  ```

- 第三个参数：`AsyncTask.doInBackground(...)`方法返回的数据类型

  ```java
  public class PhotoGalleryFragment extends Fragment{
      // ...
      // 旧版本
      private class FetchItemsTask extends AsyncTask<Void,Void,Void>{
          @Override protected Void doInBackground(Void... params){
              new FlickrFetchr().fetchItems();
              return null;
          }
      }
      // 新版本
      private class FetchItemsTask extends AsyncTask<Void,Void,List<GalleryItem>>{
          @Override protected List<GalleryItem> doInBackground(Void... params){
              return new FlickrFetchr().fetchItems();
          }
          @Override protected void onPostExecute(List<GalleryItem> items){
              mItems = items;
              setupAdapter();
          }
      }
  }
  ```

### §1.5.7 `Looper`/`Handler`/`HandlerThread`

解析JSON数据后，我们需要下载并显示图片。我们需要为`GalleryItem`实例创建相应的XML布局文件：

```xml
<!-- list_item_gallery.xml -->
<?xml version="1.0" encoding="utf-8"?>
<ImageView xmlns:android="http://schemas.android.com/apk/res/android"
    android:id="@+id/item_image_view"
    android:layout_width="match_parent"
    android:layout_height="120dp"
    android:layout_gravity="center"
    android:scaleType="centerCrop">
</ImageView>
```

`ImageView`实例由`RecyclerView`的`GridLayoutManager`实例负责管理。之前调试时，我们在`PhotoHolder`和`PhotoAdapter`中使用的是`TextView`作为演示，现在应该都改成`ImageView`：

```java
public class PhotoGalleryFragment extends Fragment{
    // ...
    private class PhotoHolder extends RecyclerView.ViewHolder{
        private ImageView mItemImageView;
        public PhotoHolder(View itemView){
            super(itemView);
            mItemImageView = (ImageView) itemView.findViewById(R.id.item_image_view);
        }
        public void bindDrawable(Drawable drawable){
            mItemImageView.setImageDrawable(drawable);
        }
    }
    private class PhotoAdapter extends RecyclerView.Adapter<PhotoHolder>{
        private List<GalleryItem> mGalleryItems;
        public PhotoAdapter(List<GalleryItem> galleryItems){
            mGalleryItems = galleryItems;
        }
        @Override public PhotoHolder onCreateViewHolder(ViewGroup viewGroup,int viewType){
            LayoutInflater inflater = LayoutInflater.from(getActivity());
            View view = inflater.inflate(R.layout.list_item_gallery,viewGroup,false);
            return new PhotoHolder(view);
        }
        @Override public void onBindViewHolder(PhotoHolder photoHolder, int position) {
            // placeholder加载固定的图像资源用于演示
            Drawable placeholder = getResources().getDrawable(R.drawable.bill_up_close);
            GalleryItem galleryItem = mGalleryItems.get(position);
            photoHolder.bindDrawable(placeholder);
        }
        @Override public int getItemCount(){
            return mGalleryItems.size();
        }
    }
    // ...
}
```

目前使用的API一次性能返回100个数据，如果一次性加载100个图片再显示的话，会耗费大量的时间和内存，因此`AsyncTask`在这时就不适用了。为了实现只加载屏幕上显示的图片，我们需要使用`Looper`对象实现对消息队列的操控。

消息循环(Message Loop)由线程和`Looper`实例构成，会不停地检查队列上是否有新消息。主线程就是一个消息循环，因此也有`Looper`实例，用于管理线程的消息队列，而`Looper`类由`HandlerThread`类管理。我们新建一个`HandlerThread`类用于实现消息队列的管理：

```java
package com.example.photogallery;
import android.os.HandlerThread;
import android.util.Log;

public class ThumbnailDownloader<T> extends HandlerThread {
    private static final String TAG = "ThumbnailDownloader";
    private Boolean mHasQuit = false;
    public ThumbnailDownloader(){
        super(TAG);
    }
    public void queueThumbnail(T target,String url){
        Log.i(TAG,"Received a url: "+url);
    }
    @Override public boolean quit(){
        mHasQuit = true;
        return super.quit();
    }
}
```

然后在`PhotoGalleryFragment`中调用该类：

```java
public class PhotoGalleryFragment extends Fragment {
    // ...
    private ThumbnailDownloader<PhotoHolder> mThumbnailDownloader;
    // ...
    @Override public void onCreate(Bundle savedInstaceState){
        // ...
        new FetchItemsTask().execute();
        mThumbnailDownloader = new ThumbnailDownloader<>();
        mThumbnailDownloader.start();
        ThumbnailDownloader.getLooper();
        Log.i(TAG,"Background thread started.")
    }
    @Override public void onDestroy(){
        super.onDestroy();
        mThumbnailDownloader.quit();
        Log.i(TAG,"Background thread destroyed.")
    }
    // ...
    private class PhotoAdapter extends RecyclerView.Adapter<PhotoHolder>{
        // ...
        @Override public void onBindViewHolder(PhotoHolder photoHolder,int position){
            Drawable placeholder = getResource().getDrawable(R.drawable.bill_up_close);
            GalleryItem galleryItem = mGalleryItems.get(position);
            photoHolder.bindDrawable(placeHolder);
            mThumbnailDownloader.QueueThumbnail(photoHolder,galleryItem.getUrl());
        }
        // ...
    }
    // ...
}
```

后台线程已经建立，接下来要使用`Message`的实例（也就是消息）来实现线程间的通信。

`Message`实例包含以下必须定义的实例字段：

- `int what`：代表消息种类的消息代码
- `Object obj`：随消息一同发送的对象
- `Handler target`：用于处理消息的`Handler`实例

```mermaid
flowchart TB
	HandlerThread["HandlerThread"]
	Looper["Looper"]
	subgraph MessageQueue ["MessageQueue"]
		message1["Message<br/>what<br/>obj<br/>target<br/>"]
		message2["Message<br/>what<br/>obj<br/>target<br/>"]
		message3["(new)Message<br/>what<br/>obj<br/>target<br/>"]
		MessageQueueObj["MessageQueue实例"]
	end
	newMessage["(new)Message"]-->Handler-->message3
	Handler["Handler"]
	message1-->Handler
	message2-->Handler
	message3-->Handler
	Handler-->Looper
	HandlerThread-->Looper
	Looper-->MessageQueueObj
```

一般情况下，我们不会去手动为`Message.target`指定`Handler`实例，而是通过`Handler.obtain-Message(Message)`来自动设置`Handler`实例。为避免重复添加已有的`Message`对象，`Handler.obtainMessage(...)`方法慧聪公共回收池中获取消息。取得`Message`实例后，可以调用`Message.sendToTarget()`方法将该实例传给发送它的`Handler`，`Handler`将其放在`Looper`消息队列的尾部：

```java
public class ThumbnailDownloader<T> extends HandlerThread {
    private static final int MESSAGE_DOWNLOAD = 0;
    private Handler mRequestHandler;
    private ConcurrentMap<T,String> mRequsetMap = new ConcurrentHashMap<>();
	// ...
    public void queueThumbnail(T target,String url){
        Log.i(TAG,"Received a url: "+url);
        if(url == null){
            mRequsetMap.remove(target);
        }else{
            mRequsetMap.put(target,url);
            mRequestHandler.obtainMessage(MESSAGE_DOWNLOAD,target).sendToTarget();
        }
    }
    // ...
}
```

解码数据流：

```java
public class ThumbnailDownloader<T> extends HandlerThread {
    // ...
    private void handleRequest(final T target){
        try {
            final String url = mRequsetMap.get(target);
            if(url == null){
                return;
            }else{
                byte[] bitmapBytes = new FlickrFetchr().getUrlBytes(url);
                final Bitmap bitmap = BitmapFactory.decodeByteArray(bitmapBytes,0, bitmapBytes.length);
                Log.i(TAG,"Bitmap created.");
            }
        } catch (IOException ioException) {
            Log.e(TAG,"Error downloading image",ioException);
        }
    }
    @Override protected void onLooperPrepared(){
        mRequestHandler = new Handler(){
            @Override public void handleMessage(Message msg){
                if(msg.what == MESSAGE_DOWNLOAD){
                    T target = (T) msg.obj;
                    Log.i(TAG,"Got a request for URL: " + mRequsetMap.get(target));
                    handleRequest(target);
                }
            }
        };
    }
    // ...
}
```

```mermaid
flowchart LR
	subgraph ThumbnailDownloader ["ThumbnailDownloader"]
		subgraph Variable ["类字段/实例字段"]
			mRequestMap["ConcurrentMap&lt;T,String&gt; mRequest"]
			mHasQuit["Boolean mHasQuit = false"]
			mRequestHandler["Handler mRequestHandler"]
		end
		subgraph handleRequest ["void handleRequest(final T target)"]
			handleRequest1{"mRequestMap<br>.get(target)"}
			handleRequest2["return"]
			handleRequest3["byte[] bitmapBytes = new FlickrFetchr.getUrlBytes(url)"]
			handleRequest4["Bitmap bitmap = BitmapFactory<br/>.decodeByteArray(bitmapBytes,0,bitmapBytes.length)"]
			handleRequest1--"null"-->handleRequest2
			handleRequest1--"非null"-->handleRequest3
			handleRequest3-->handleRequest4
			handleRequest4-->handleRequest2
			mRequestMap.->handleRequest1
		end
		subgraph onLooperPrepared ["void onLooperPrepared()"]
			subgraph onLooperPrepared0 ["mRequestHandler = new Handler()<br/>{@Override handleMessage(Message msg)}"]
				onLooperPrepared1{"msg.what"}
				onLooperPrepared2["return"]
				onLooperPrepared3["T target - (T) target"]
				onLooperPrepared4["handleRequest(target)"]
			end
			mRequestHandler.->onLooperPrepared1
			onLooperPrepared1--"非0"-->onLooperPrepared2
			onLooperPrepared1--"0"-->onLooperPrepared3
			onLooperPrepared3-->onLooperPrepared4
			onLooperPrepared4-->onLooperPrepared2
			handleRequest2.->onLooperPrepared4
		end
		subgraph queueThumbnail ["void queueThumbnail(T target,String url)"]
			queueThumbnail1{"url==null?"}
			queueThumbnail2["mRequestMap.remove(target)"]
			queueThumbnail3["mRequestMap.put(target,url)"]
			queueThumbnail4["mRequestHandler<br/>.obtainMessage(0,target)<br/>.sendToTarget()"]
			queueThumbnail1--"url==null"-->queueThumbnail2
			queueThumbnail1--"url!=null"-->queueThumbnail3-->queueThumbnail4
			queueThumbnail4.->mRequestMap
		end
	end
```

然后用`Handler`向主线程发送请求：

```mermaid
flowchart LR
	subgraph PhotoGalleryFragment ["PhotoGalleryFragment"]
		PhotoGalleryFragmentThread["主线程"]
		PhotoGalleryFragmentHandler["Handler"]
	end
	subgraph ThumbnailDownloader ["ThumbnailDownloader"]
		ThumbnailDownloaderThread["下载管理线程"]
		ThumbnailDownloaderHandler["Handler"]
	end
	subgraph FlickrFetchr ["FlickrFetchr"]
		FlickrFetchrThread["网络线程"]
	end
	PhotoGalleryFragmentThread--"下载图片"-->ThumbnailDownloaderThread
	ThumbnailDownloaderThread--"下载图片"-->FlickrFetchrThread
	FlickrFetchrThread--"返回图片数据流byte[]"-->ThumbnailDownloaderThread
	ThumbnailDownloaderThread=="mRequestHandler<br/>存储Bitmap到HashMap"==>ThumbnailDownloaderHandler
	ThumbnailDownloaderThread=="mResponseHandler"==>PhotoGalleryFragmentHandler
```

```java
public class ThumbnailDownloader<T> extends HandlerThread {
    // ...
    private Handler mRequestHandler;
    private Handler mResponseHandler;
    private ThumbnailDownloadListener<T> mThumbnailDownloadListener;
	// ...
    public interface ThumbnailDownloadListener<T>{
        void onThumbnailDownloaded(T target,Bitmap thumbnail);
    }
    public void setThumbnailDownloadListener(ThumbnailDownloadListener<T> listener){
        mThumbnailDownloadListener = listener;
    }
    public ThumbnailDownloader(Handler responseHandler){
        super(TAG);
        mResponseHandler = responseHandler;
    }
}
```

现在当创建`ThumbnailDownloader`实例时，必须给构造方法提供`Handler responseHandler`实例（至于`Handler requestHandler`则由其内部的`@Override onLooperPrepared(...)`方法来创建），所以需要更新`PhotoGalleryFragment.java`中的创建`ThumbnailDownloader`实例相关的代码：

```java
public class PhotoGalleryFragment extends Fragment {
    // ...
    @Override public void onCreate(Bundle savedInstanceState){
        super.onCreate(savedInstanceState);
        setRetainInstance(true);
        new FetchItemsTask().execute();
        
        Handler responseHandler = new Handler();
        mThumbnailDownloader = new ThumbnailDownloader<>(responseHandler);
        mTHumbnailDOwnloader.setThumbnailDownloadListener(
        	new ThumbnailDownloader.ThumbnailDownloadListener<PhotoHolder>(){
                @Override public void onThumbnailDownloaded(PhotoHolder photoHolder,Bitmap bitmap){
                    Drawable drawable = new BitmapDrawable(getResources(),bitmap);
                    photoHolder.bindDrawable(drawable);
                }
            }
        );
        mThumbnailDownloader.start();
        mThumbnailDownloader.getLooper();
        Log.i(TAG,"Background thread started.");
    }
    // ...
}
```

这里定义的`mResponseHandler`是在主线程的`onCreate(...)`方法中创建的，所以会自动关联到主线程的`Looper`上。`Handler.post(Runnable)`可用于发布`Message`：

```java
public class ThumbnailDownloader<T> extends HandlerThread {
    // ...
    private void handleRequest(final T target){
        try{
            final String url = mRequestMap.get(target);
            if(url == null){
                return;
            }else{
                byte[] bitmapBytes = new FlickrFetchr().getUrlBytes(url);
                final Bitmap bitmap = BitmapFactory.decodeByteArray(bitmapBytes,0,bitmapBytes.length);
                
                mResponseHandler.post(new Runnable{
                    @Override public void run(){
                        if(mRequestMap.get(target) != url || mHasQuit){
                            return;
                        }else{
                            mRequestMap.remove(target);
                            mThumbnailDownloadListener.onThumbnailDownloaded(target,bitmap);
                        }
                    }
                });
            }
        }catch(IOException ioException){
            Log.e(TAG,"Error downloading image",ioException);
        }
    }
    // ...
}
```

再新建一个方法，用于清除队列中的所有请求：

```java
public class ThumbnailDownloader<T> extends HandlerThread {
    // ...
    public void clearQueue(){
        mRequestHandler.removeMessaged(MESSAGE_DOWNLOADED);
        mRequestMap.clear();
    }
    // ...
}
```

然后在`PhotoGalleryFragment`类中调用该方法：

```java
public class PhotoGalleryFragment extends Fragment {
    // ...
    @Override public void onDestroyView(){
        super.onDestroyView();
        mThumbnailDownloader.clearQueue();
    }
    // ...
}
```

### §1.5.8 SearchView

`SreachView`是Android SDK自带的组件，可以实现搜索功能。

搜索功能自然会涉及到API，我们先重构一下API：

```java
public class FlickrFetchr {
    // ...
    private static final String FETCH_RECENTS_METHOD = "flickr.photos.getRecent";
	private static final String SEARCH_METHOD = "flickr.photos.search";
    private static final Uri ENDPOINT = Uri.parse("https://api.flickr.com/services/rest")
        .buildUpon()
        .appendQueryParameter("api_key",API_KEY)
        .appendQueryParameter("format","json")
        .appendQueryParameter("nojsoncallback","1")
        .appendQueryParameter("extras","url_s")
        .build();
}
```

重写`FlickrFetchr`中的`fetchItems()`方法：

```java
public class FlickrFetchr {
    // ...
    public List<GalleryItem> downloadGalleryItems(String url){
        List<GalleryItem> items = new ArrayList<>();
        try {
            String jsonString = getUrlString(url);
            Log.i(TAG,"Received JSON: " + jsonString);
            JSONObject jsonBody = new JSONObject(jsonString);
            parseItems(items,jsonBody);
        }catch (IOException ioException){
            Log.e(TAG,"Failed to fetch items",ioException);
        }catch (JSONException jsonException){
            Log.e(TAG,"Failed to parse JSON");
        }
        return items;
    }
    public String buildUrl(String method,String query){
        Uri.Builder uriBuilder = ENDPOINT.buildUpon()
                .appendQueryParameter("method",method);
        if(method.equals(SEARCH_METHOD)){
            uriBuilder.appendQueryParameter("text",query);
        }
        return uriBuilder.build().toString();
    }
    public List<GalleryItem> fetchRecentPhotos() {
        String url = buildUrl(FETCH_RECENTS_METHOD,null);
        return downloadGalleryItems(url);
    }
    public List<GalleryItem> fetchPhotos(String query) {
        String url = buildUrl(SEARCH_METHOD,query);
        return downloadGalleryItems(url);
    }
    // ...
}
```

接着更改`PhotoGalleryFragment`中相应的调用方法：

```java
public class PhotoGalleryFragment extends Fragment {
    // ...
    private class FetchItemsTask extends AsyncTask<Void,Void,List<GalleryItem>> {
        @Override protected List<GalleryItem> doInBackground(Void... params) {
        	//硬编码用于测试
            String query = "robot";
            if(query == null){
                return new FlickrFetchr().fetchRecentPhotos();
            }else{
                return new FlickrFetchr.searchPhotos(query);
            }
        }
        // ...
    }
    // ...
}
```

搜索功能已经完成，现在需要创建相应的搜索界面：

```xml
<!-- string.xml -->
<resources>
	<!-- ... -->
    <string name="search">Search</string>
    <string name="clear_search">Clear Search</string>
    <!-- ... -->
</resources>
```

```xml
<!-- res/menu/fragment_photo_gallery.xml -->
<?xml version="1.0" encoding="utf-8"?>
<menu xmlns:android="http://schemas.android.com/apk/res/android"
    xmlns:app="http://schemas.android.com/apk/res-auto">
    <item
        android:id="@+id/menu_item_search"
        android:title="@string/search"
        app:actionViewClass="androidx.appcompat.widget.SearchView"
        app:showAsAction="ifRoom" />
    <item
        android:id="@+id/menu_item_clear"
        android:title="@string/clear_search"
        app:showAsAction="never" />
</menu>
```

在`PhotoGalleryFragment`类中启用菜单：

```java
public class PhotoGalleryFragment extends Fragment {
    // ...
    @Override public void onCreate(Bundle savedInstanceState){
        super.onCreate(savedInstanceState);
        setRetainInstance(true);
        setHasOptionsMenu(true);
        updateItems();
        // ...
    }
    // ...
    @Override void onCreateOptionsMenu(Menu menu, MenuInflater menuInflater){
        super.onCreateOptionsMenu(menu,menuInflater);
        menuInflater.inflate(R.menu.fragment_photo_gallery,menu);
    	MenuItem searchItem = menu.findItem(R.id.menu_item_search);
        final SearchView searchView = (searchView) searchItem.getActionView();
    	searchView.setOnQueryTextListener(new SearchView.OnQueryTextListener(){
            @Override public boolean onQueryTextSubmit(String query) {
                Log.d(TAG,"QueryTextSubmit: " + query);
                updateItems();
                return true;
            }
            @Override public boolean onQueryTextChange(String newText) {
                Log.d(TAG,"QueryTextChange: " + newText);
                return false;
            };
        });
    }
    private void updateItems(){
        new FetchItemsTask().execute();
    }
    // ...
}
```

`onCreateOptionsMenu(...)`方法先将整个菜单实例化成`MenuItem`实例并存储于`searchItem`字段中，然后利用`(SearchView) MenuItem.getActionView()`得到相应的`SearchView`实例`searchView`，并为其设置监听器`setOnQueryTextListener()`。

为了保存和查询搜索历史记录，新建一个`QueryPreferences`类，通过`Shared Preferences`这一机制来实现该功能：

```java
package com.example.photogallery;

import android.content.Context;
import android.preference.PreferenceManager;

public class QueryPreferences {
    private static final String PREF_SEARCH_QUERY = "searchQuery";
    public static String getStoredQuery(Context context){
        return PreferenceManager.getDefaultSharedPreferences(context)
                .getString(PREF_SEARCH_QUERY,null);
    }
    public static void setStoredQuery(Context context,String query){
        PreferenceManager.getDefaultSharedPreferences(context)
                .edit()
                .putString(PREF_SEARCH_QUERY,query)
                .apply();
    }
}
```

然后在`PhotoGalleryFragment`中调用该类：

```java
public class PhotoGalleryFragment extends Fragment {
    // ...
    @Override public void onCreateOptionsMenu(Menu menu,MenuInflater menuInflater) {
        // ...
        searchView.setOnQueryTextListener(new SearchView.OnQueryTextListener(){
            @Override public boolean onQueryTextSubmit(String query){
                QueryPreferences.setStoredQuery(getActivity(),query);
                // ...
            }
            // ...
        });
        // ...
    }
    @Override public boolean onOptionsItemSelected(MenuItem item){
        switch(item.getItemId()){
            case R.id.menu_item_clear:
                QueryPreferences.setStoredQuery(getActivity,null);
                updateItems();
                return true;
            default:
                return super.onOptionsItemSelected(item);
        }
    }
}
```

最后更新`FetchItemsTask`，查询字符串不再使用硬编码以供调试：

```java
public class PhotoGalleryFragment extends Fragment{
    // ...
    private void updateItems(){
        String query = QueryPreferences.getStoredQuery(getActivity());
        new FetchItemsTask(query).execute();
    }
    private class FetchItemsTask extends AsyncTask<Void,Void,List<GalleryItem>>{
        private String mQuery;
        public FetchItemsTask(String query){
            mQuery = query;
        }
        @Override protected List<GalleryItem> doInBackground(Void... params){
            if(mQuery == null)
                // ...
        }
        // ...
    }
}
```

当点击搜索按钮时，文本框应该显示保存的字符串：

```java
public class PhotoGalleryFragment extends Fragment {
    // ...
    @Override public void onCreateOptionsMenu(Menu menu,MenuInflater menuInflater){
        // ...
        searchView.setOnSearchClickListener(new View.OnClickListener(){
        	@Override public void onClick(View v){
                String query = QueryPreferences.getStoredQuery(getActivity());
                searchView.setQuery(query,false);
            } 
        });
        // ...
    }
    // ...
}
```

### §1.5.9 `IntentService`

目前为止，我们开发的所有应用都离不开`Activity`。如果不给用户提供界面，例如在后在下载图片，则可以使用`IntentService`来创建相应的服务。下面新建一个`IntentService`的子类`PollService`：

```java
public class PollService extends IntentService {
    private static final String TAG = "PollService";
    public static Intent newIntent(Context context){
        return new Intent(context,PollService.class);
    }
    public PollService(){
        super(TAG);
    }
    @Override protected void onHandleIntent(Intent intent){
        Log.i(TAG,"Received an intent: " + intent);
    }
}

```

这是一个最基本的`IntentService`。首先，这是一个`Context`的子类`ContextWrapper`的子类`Service`的子类。然后，这个子类中自带`onHandleIntent(Intent)`，意味着该子类能够响应`Intent`实例。该方法将传入的`Intent`实例放入执行队列，依次执行相应的`onHandleIntent(Intent)`方法，执行完毕以后对应的`Intent`实例就被销毁，当执行队列中的所有`Intent`实例均被销毁后，`IntentService`也会随之销毁。

创建的服务必须在`AndroidManifest.xml`中声明：

```xml
<manifest>
	<!-- ... -->
    <application>
    	<!-- ... -->
        <service android:name=".PollService"/>
    </application>
</manifest>
```

添加服务启动代码：

```java
public class PhotoGalleryFragment extends Fragment {
    // ...
    @Override public void onCreate(Bundle savedInstanceState){
        // ...
        Intent i = PollService.newIntent(getActivity());
        getActivity().startService(i);
    }
}
```

此时运行APP，可以在Logcat中看到服务创建成功的日志：

```logcat
2022-01-30 23:24:41.298 3895-3944/com.example.photogallery I/PollService: Received an intent: Intent { cmp=com.example.photogallery/.PollService }
```

为保证后台网络连接的安全性，我们需要使用`ConnectivityManager`类来确定网络连接是否可用：

```java
public class PollService extends IntentService {
    // ...
    @Override protected void onHandleIntent(Intent intent){
        if(!isNetworkAvailableAndConnected()){
            return;
        }else{
            Log.i(TAG,"Received an intent: " + intent);
        }
    }
    private boolean isNetworkAvailableAndConnected(){
        ConnectivityManager connectivityManager = (ConnectivityManager) getSystemService(CONNECTIVITY_SERVICE);
        boolean isNetworkConnected =
                (connectivityManager.getActiveNetworkInfo() != null) && (connectivityManager.getActiveNetworkInfo().isConnected());
        return isNetworkConnected;
    }
}
```

与此同时还要在`AndroidManifest.xml`中申请`ACCESS_NETWORK_STATE`权限：

```xml
<manifest>
	<!-- ... -->
	<uses-permission android:name="android.permission.ACCESS_NETWORK_STATE"/>
	<!-- ... -->
</manifest>
```

将后台服务最近一次的查询结果保存在Shared Preferences中：

```java
public class QueryPreferences {
    // ...
    private static final String PREF_LAST_RESULT_ID = "lastResultId";
    // ...
    public static String getLastResultId(Context context){
        return PreferenceManager.getDefaultSharedPreferences(context)
            .getString(PREF_LAST_RESULT_ID,null);
    }
    public static void setLastResultId(Context context,String lastResultId){
        PreferenceManager.getDefaultSharedPreferences(context)
            .edit()
            .putString(PREF_LAST_RESULT_ID,lastResultId)
            .apply();
    }
}
```

后台服务需要实现以下功能：

- 从默认Shared Preferences中获取当前查询结果和上一次查询结果ID
- 调用FlickrFetchr类获取最新查询结果
- 如果有结果返回，则抓取第一条结果
- 确认是否不同于上一次结果ID
- 将第一条结果存入Shared Preferences

代码如下：

```java
public class PollService extends IntentService {
    // ...
    @Override protected void onHandleIntent(Intent intent){
        // ...
        Log.i(TAG,"Received an intent: " + intent);
        String query = QueryPreferences.getStoredQuery(this);
        String lastResultId = QueryPreferences.getLastResultId(this);
        List<GalleryItem> items;
        if(query == null)
        	{items = new FlickrFetchr().fetchRecentPhotos();}
        else
        	{items = new FlickrFetchr().searchPhotos(query);}
        if(items.size() == 0)
        	{return;}
        else
        	{
            	String resultId = items.get(0).getId();
            	if(resultId.equals(lastResultId))
                	{Log.i(TAG,"Got an old result: " + resultId);}
            	else
                	{Log.i(TAG,"Got a new result: " + resultId);}
            	QueryPreferences.setLastResultId(this,resultId);
        	}
    }
    // ...
}
```

### §1.5.10 `AlarmManager`

现在我们的服务已经初具雏形，但是仍然不具备“后台”这个特点。因为要运行`PollService`服务，就必须保证`PhotoGalleryFragment.onCreate(...)`方法被调用，即必须存在一个`PhotoGalleryFragment`实例，而该实例只能由`PhotoGalleryActivity`创建——总而言之，当前的服务必须依赖于`Activity`的存在才能存在。

如何在没有`Activity`运行的情况下，实现真正的“后台”服务呢？

- 在`Handler.sendMessageDelayed(...)`或`Handler.postDelayed(...)`中调用

  这种方法的缺点是，服务仍然没有摆脱对`Activity`的依赖。因为用户离开当前应用时，主进程就会停止，其附着的一系列`Handler`也会随之销毁，相当于`IntentService`以来`Handler`，`Handler`依赖`Activity`，相当于`IntentService`仍然依赖着`Activity`。

- 调用`AlarmManager`

  `AlarmManager`是系统服务，用于发送由`PendingIntent`的打包的`Intent`。

```java
public class PollService extends IntentService {
    // ...
    private static final long POLL_INTERVAL_MS =
        TimeUnit.MINUTES.toMillis(1);
    // ...
    public static void setServiceAlarm(Context context,boolean isOn){
        Intent intent = PollService.newIntent(context);
        PendingIntent pendingIntent = PendingIntent.getService(
            context,
            0,
            intent,
            0);
        
        AlarmManager alarmManager = (AlarmManager) context.getSystemService(Context.ALARM_SERVICE);
        if(isOn){
            alarmManager.setRepeating(
                    AlarmManager.ELAPSED_REALTIME,
                    SystemClock.elapsedRealtime(),
                    POLL_INTERVAL_MS,
                    pendingIntent);
        }else{
            alarmManager.cancel(pendingIntent);
            pendingIntent.cancel();
        }
    }
    // ...
}
```

`PendingIntent.getSerivce(...)`返回一个`PendingIntent`实例。在本例中，该实例用于启动`PollService`。该方法有四个参数：

- `Context context`：将传入的`Context`实例进行打包，打包到这个`PendingIntent`实例中
- `int requestCode`：用于标识`PendingIntent`实例来源
- `@NonNull Intent intent`：待发送的`Intent`对象
- `@Flags int flags`：指定创建`PendingIntent`使用的方法标志符

设置定时器可调用`AlarmManager.setRepeating(...)`方法，该方法同样包括四个参数：

- `@AlarmType int type`：指定定时器时间基准的常量

  本例中我们使用的是`AlarmManager.ELAPSED_REALTIME`，即定时器使用的时间基准是由`SystemClock.elapsedRealtime()`方法走过的时间确定的。

- `long triggerAtMillis`：定时器启动的时间

- `long intervalMillis`：定时器循环的时间间隔

- `PendingIntent operation`：到时要发送的`PendingIntent`实例

取消定时器可调用`AlarmManager.cancel(PendingIntent)`方法。

现在我们终于可以删除依赖于`Activity`的服务代码，转而使用依赖于系统服务`AlarmManager`的后台服务了：

```java
public class PhotoGalleryFragment extends Fragment {
    // ...
    @Override public void onCreate(Bundle savedInstanceState){
        // ...
        updateItems();
        
        PollService.setServiceAlarm(getActivity(),true);
        
        Handler responseHandler = new Handler();
        // ...
    }
    // ...
}
```

`AlarmManager`是系统服务，如果一个恶意服务：

- 寄存于`AlarmManager`
- 永不调用`alarmManager.cancel(pendingIntent)`和`pendingIntent.cancel()`以销毁服务
- 设置定时器定期启动服务（即使服务已经启动）

这个恶意服务将永远运行下去，从而造成极大的电量消耗和流量开支。除此之外，每一次启动服务都会导致设备被唤醒。要彻底清除这种定时自动启动的服务，只能卸载相应的APP。

因此，我们需要限制服务启动的频度。现有的解决方案有：

- 非精准重复

  在本例中，我们调用`AlarmManager.setRepeating(...)`调用`AlarmManager.ELAPSED_REALTIME`常量设置了一个精确的一分钟计时器。如果该Android系统上运行着$10$个类似的不同时间启动的服务，那么一个小时内设备就会被唤醒$600$次，这是一个非常恐怖的频率。事实上，该方法也可以设置一个非精准的重复值，使得这些服务即使不是在同一时间启动的，也能保证屏幕一小时内只被唤醒`60`次。

  - `AlarmManager.ELAPSED_REALTIME`使用最近一次屏幕被亮起的时间开始计时
  - `AlarmManager.RTC`使用UTC时间，但是没有考虑失去的影响

  以上的常量有一个特性：如果屏幕处于黑屏状态，那么即使已经到时间了，定时器也不会被触发。以下的常量没有该限制：

  - `AlarmManager.ELAPSED_REALTIME_WAKEUP`
  - `AlarmManager.RTC_WAKEUP`

### §1.5.11 再探`PendingIntent`

我们已经知道，`AlarmManager`是系统服务，用于发送由`PendingIntent`的打包的`Intent`。实质上，`PendingIntent`是从`Object`直接延伸出的子类。

`PendingIntent.getService(...)`方法返回一个`PendingIntent`实例。值得注意的是,该`Intent`实例对应的`PendingIntent`实例是由Android主线程创建的，APP中同一个`Intent`中得到的实例只是该实例的一个指针副本。因此可以借此测试某个`Intent`是否创建过`PendingIntent`，或者将其撤销。撤销时首先调用`AlarmManager.cancel(PendingIntent)`撤销该`PendingIntent`实例的计时器，然后再销毁该`PendingIntent`实例。一个`PendingIntent`只能登记一个定时器。

综上所述，我们可以通过检测`PendingIntent`实例是否存在，来推断定时器是否激活：

```java
public class PollService extends IntentService {
    // ...
    public static boolean isServiceAlarmOn(Context context){
        Intent intent = PollService.newIntent(context);
        PendingIntent pendingIntent = PendingIntent.getService(
        	context,
        	0,
        	intent
        	PendingIntent.FLAG_NO_CREATE);
        return pendingIntent != null;
    }
    // ...
}
```

既然现在可以通过销毁`PendingIntent`实例来停止计时器，也可以通过`PendingIntent`实例的指针引用特性来判断计时器是否运行，我们就可以不用非得在`PhotoHalleryFragment.onCreate(...)`中强制启动后台服务，而是在图形界面里控制定时器的开关：

```xml
<!-- res/values/strings.xml -->
<resources>
	<!-- ... -->
    <string name="start_polling">Start Polling</string>
    <string name="stop_polling">Stop Polling</string>
    <string name="new_pictures_title">New PhotoGallery Pictures</string>
    <string name="new_pictures_text">You have new pictures in PhotoGallery.</string>
</resources>
```

```xml
<!-- menu/fragment_photo_gallery.xml -->
<menu>
	<!-- ... -->
    <item
        android:id="@+id/menu_item_toggle_polling"
        android:title="@string/start_polling"
        app:showAsAction="ifRoom"/>
</menu>
```

```java
public class PhotoGalleryFragment extends Fragment {
    // ...
    @Override public void onCreate(Bundle savedInstanceState){
        // ...
        updateItems();
        // 删除PollService.setServiceAlarm(getActivity(),true);
        Handler responseHandler = new Handler();
        // ...
    }
    @Override public void onOptionsItemSelected(MenuItem item){
        switch (item.getItemId()){
            case R.id.menu_item_clear:
                // ...
            case R.id.menu_item_toggle_polling:
                boolean shouldStartAlarm = !PollService.isServiceAlarmOn(getActivity());
                PollService.setServiceAlarm(getActivity(),shouldStartAlarm);
                return true;
            default:
                // ...
        }
    }
    @Override public void onCreateOptionsMenu(Menu menu,MenuInflater menuInflater){
        // ...
        MenuItem toggleItem = menu.findItem(R.id.menu_item_toggle_polling);
        if(PollService.isServiceAlarmOn(getActivity())){
            toggleItem.setTitle(R.string.stop_polling);
        }else{
            toggleItem.setTitle(R.string.start_polling);
        }
    }
    // ...
}
```

还有一个问题，我们点击Start Polling按钮时，按钮的文字并没有向我们预期的那样变成Stop Polling，这是因为菜单不像其他组件那样可以自动更新UI。因此，我们需要手动调用更新方法：

```java
public class PhotoGalleryFragement extends Fragment {
    // ...
    @Override public boolean onOptionsItemSelected(MenuItem item){
        switch(item.getItemId()){
            case R.id.menu_item_clear:
                // ...
            case R.id.menu_item_toggle_polling:
                //...
                getActivity().invalidateOptionsMenu();
                return true;
            default:
                // ...
        }
    }
    // ...
}
```

### §1.5.12 `Notification`

我们知道，XML布局文件中的组件通过`Fragment`和`Activity`与用户进行交互，同理`IntentService`也可以通过`Notification`与用户进行交互。一个完整的`Notification`对象包括以下内容：

- Lollopop之前的设备在状态栏上显示的`ticker text`
- 在状态栏上显示的图标
- 通信信息自身的视图
- 等待用于点击通知以触发的`PendingIntent`

首先添加一个方法，返回一个用于启动`PhotoGalleryActivity`的`Intent`实例：

```java
public class PhotoGalleryActivity extends SingleFragmentActivity{
    public static Intent newIntent(Context context){
        return new Intent(context,PhotoGalleryActivity.class);
    }
    // ...
}
```

```java
public class PollService extends IntentService {
    // ...
    @Override protected void onHandleIntent(Intent intent){
        // ...
        if(items.size() == 0){
            return;
        }else{
            String resultId = items.get(0).getId();
            if(resultId.equals(lastResultId)){
                Log.i(TAG,"Got an old result: " + resultId);
            }else{
                Log.i(TAG,"Got a new result: " + resultId);
                Resources resources = getResources();
                Intent newIntent = PhotoGalleryActivity.newIntent(this);
                PendingIntent pendingIntent = PendingIntent.getActivity(this,0,newIntent,0);
                Notification notification = new NotificationCompat.Builder(this)
                    // 设置ticker text
                    .setTicker(resources.getString(R.string.new_pictures_title))
                    // 设置小图标,使用Android Framework自带的资源
                    .setSmallIcon(android.R.drawable.ic_menu_report_image)
                    // 设置标题
                    .setContentTitle(resources.getString(R.string.new_pictures_text))
                    // 设置内容
                    .setContentText(resources.getText(R.string.new_pictures_text))
                    // 点击时触发的PendingIntent实例
                    .setContentIntent(pendingIntent)
                    // 点击该通知后自动从消息抽屉中删除
                    .setAutoCancel(true)
                    .build();
                // 从当前Context实例中取出NotificationManagerCompat实例
                NotificationManagerCompat notificationManager = NotificationManagerCompat.from(this);
                // 贴出消息
                notificationManager.notify(0,notification);
            }
            // ...
        }
    }
    // ...
}
```

> 注意：`NotificationManager.notify(@Nullable String tag,int id,@NonNull Notification notification)`中的参数`id`用于唯一地标识通知。如果重复调用相同语句两次，则第一次产生的通知就会被第二次产生的通知替换掉。在实际开发中，常常利用这种方法实现通知栏的动态视觉效果。

服务的生命周期之间有以下回调方法：

- `onCreate(...)`：创建服务时调用
- `onStartCommand(Intent,int,int)`：组件通过`startService(Intent)`方法启动服务时调用。第一个`int`标识符用来表示`intent`的发送状态（重新发送/从未成功过的发送），第二个`int`启动ID用于区分不同的命令
- `onDestroy(...)`：删除服务时调用

### §1.5.13 `BroadcastIntentReceiver`

除了自定义发送的`Intent`，Android系统也会发送`Intent`。例如WIFI切换、电话接听、短信收发、软件装卸，都会产生对应的事件，并向系统广播对应的`BroadcastIntent`实例。

```mermaid
flowchart TB
	subgraph Intent ["Intent"]
		PhotoGalleryOfIntent[PhotoGallery创建的组件]
		AndroidOfIntent[Android的ActivityManager]
		OtherApp[其他应用的任意组件]
		PhotoGalleryOfIntent-->AndroidOfIntent-->OtherApp
	end
	subgraph BroadcastIntent ["BroadcastIntent"]
		PhotoGalleryOfBroadcastIntent[PhotoGallery创建的组件]
		AndroidOfBroadcastIntent[Android的ActivityManager]
		OtherApp1[其他应用的任意组件]
		OtherApp2[其他应用的任意组件]
		OtherApp3[其他应用的任意组件]
		OtherApp4[......]
		PhotoGalleryOfBroadcastIntent-->AndroidOfBroadcastIntent
		AndroidOfBroadcastIntent-->OtherApp1
		AndroidOfBroadcastIntent-->OtherApp2
		AndroidOfBroadcastIntent-->OtherApp3
		AndroidOfBroadcastIntent-->OtherApp4
	end
```

为了实现开启自动启动，我们需要在`AndroidManifest.xml`中添加用于监测BOOT是否完成的权限：

```xml
<manifest>
	<!-- ... -->
    <uses-permission android:name="android.permission.RECEIVE_BOOT_COMPLETED"/>
    <application>
    	<!-- .. -->
        <receiver android:name=".StartupReceiver">
            <intent-filter>
                <action android:name="android.intent.action.BOOT_COMPLETED"/>
            </intent-filter>
        </receiver>
    </application>
</manifest>
```

创建一个BroadcastReceiver类：

```java
public class StartupReceiver extends BroadcastReceiver {
    private static final String TAG = "StartupReceiver";
    @Override public void onReceive(Context context, Intent intent){
        Log.i(TAG,"Received broadcast intent: " + intent.getAction());
    }
}
```

现在`android.intent.action.BOOT_COMPLETED`已经绑定到了`.StartupService`这一`Receiver`。Android一旦产生`BOOT_COMPLETE`事件，就会调用`StartupReceiver.onReceive(...)`方法。

`Receiver`需要知道定时器的启停状态，可以存储在`QueryPreferences`类中：

```java
public class QueryPreferences {
    // ...
    private static final String PREF_IS_ALARM_ON = "isAlarmOn";
    // ...
    public static boolean isAlarmOn(Context context){
        return PreferenceManager.getDefaultSharedPreferences(context)
            .getBoolean(PREF_IS_ALARM_ON,false);
    }
    public static void setAlarmOn(Context context,boolean isOn){
        PreferenceManager.getDefaultSharedPreferences(context)
            .edit()
            .putBoolean(PREF_IS_ALARM_ON,isOn)
            .apply();
    }
}
```

在`PollSerivce`服务中调用`QueryPreferences`类中新添的方法：

```java
public class PollService extends IntentService {
    // ...
    public static void serServiceAlarm(Context context,boolean isOn){
        // ...
        QueryPreferences.setAlarmOn(context,isOn);
    }
    // ...
}
```

在`StartupReceiver`中启动定时器：

```java
public class StartupReceiver extends BroadcastReceiver{
    // ...
    @Override public void onReceive(Context context,Intent intent){
        // ...
        boolean isOn = QueryPreferences.isAlarmOn(context);
        PollService.setServiceAlarm(context,ison);
    }
}
```

现在通知功能可以运作了，但是在APP前台也会运作，我们需要解决这个BUG：

```java
public class PollService extends IntentService {
    // ...
	private static final String ACTION_SHOW_NOTIFICATION = "com.example.photogallery.SHOW_NOTIFICATION";
	// ...
    @Override protected void onHandleIntent(Intent intent){
        if(items.size() == 0){
            return;
        }else{
            // ...
            if(resultId.equals(lastResultId)){
                // ...
            }else{
            	// ...
                sendBroadcast(new Intent(ACTION_SHOW_NOTIFICATION));
            }
            // ...
        }
    }
    // ...
}
```

新建一个抽象类`VisibleFragment`：

```java
public abstract class VisibleFragment extends Fragment {
    private BroadcastReceiver mOnShowNotification = new BroadcastReceiver() {
        @Override public void onReceive(Context context, Intent intent) {
            Toast.makeText(
                getActivity(),
                "Got a broadcast:" + intent.getAction(),
                Toast.LENGTH_LONG
            ).show();
        }
    };
    private static final String TAG = "VisibleFragment";
    @Override public void onStart(){
        super.onStart();
        IntentFilter filter = new IntentFilter(PollService.ACTION_SHOW_NOTIFICATION);
        getActivity().registerReceiver(mOnShowNotification,filter);

    }
    @Override public void onStop(){
        super.onStop();
        getActivity().unregisterReceiver(mOnShowNotification);
    }
}
```

接下来修改`PhotoGalleryFragment`类，使其继承与刚才新建的抽象类：

```java
public class PhotoGalleryFragment extends VisibleFragment {
    // ...
}
```

为了让其他APP不能监听并触发自己的`Receiver`，有以下两种方法：

- 在`AndroidManifest.xml`中声明`<receiver>`的属性`android:exported`为`false`

  ```xml
  <resource>
  	<!-- ... -->
      <activity>
      	<!-- ... -->
          <receiver android:name=".StartupReceivver"
                    android:exported="false">
          	<!-- ... -->
          </receiver>
      </activity>
  </resource>
  ```

- 在`AndroidManifest.xml`中声明私有权限

  ```xml
  <resource>
  	<permission android:name="com.example.photogallery.PRIVATE"
                  android:protectionLevel="signature"/>
      <!-- ... -->
      <uses-permission android:name="com.example.photogallery.PRIVATE"/>
  	<!-- ... -->
  </resource>
  ```
  
  > 要自定义权限，就必须指定`android:protectionLevel`指定安全级别。该属性有可选值如下：
  >
  > | `android:protectionLevel`可选值 | 用法                                                         |
  > | ------------------------------- | ------------------------------------------------------------ |
  > | `normal`                        | 用于阻止应用执行危险操作（访问个人隐私数据、位置信息、发送短信等），单用户不会被明确要求给予授权。 |
  > | `dangerous`                     | 用于除`normal`之外的其他所有危险操作，从`Marshmallow`开始，从`Marshmallow`该版本开始，该安全等级的权限都需要调用`requestPermission(...)`方法明确要求用户授权。 |
  > | `signature`                     | 只有当应用签署了与被声明应用一致的安全证书时，才授予在被声明应用中的相应权限，反之则拒绝，整个过程不会明确提示用户授权成功或失败的信息。 |
  > | `signatureOrSystem`             | 只有当应用签署了与被声明应用一致的安全证书时，才授予在Android系统镜像涵盖的所有包中的所有权限，反之则拒绝，整个过程不会明确提示用户授权成功或失败的信息。 |

发送带有权限的`Broadcast`：

```java
public class PollService extends IntentService {
    // ...
    public static final String PREM_PRIVATE = "com.example.photogallery.PRIVATE";
    // ...
    @Override protected void onHandleIntent(Intent intent){
        // ...
        if(item.size() == 0){
            return;
        }else{
            String resultId = items.get(0).getId();
            if(resultId.equals(lastResultId)){
                // ...
            }else{
                // ...
                sendBroadcast(new Intent(ACTION_SHOW_NOTIFICATION),PERM_PRIVATE);
            }
        }
    }
    // ...
}
```

接受带权限的`Broadcast`：

```java
public abstract class VisibleFragment extends Fragment {
    // ...
    @Override public void onStart(){
        // ...
        getActivity().registerReceiver(
            mOnShowNotification,
            filter,
            PollService.PERM_PRIVATE,
            null
        );
    }
    // ...
}
```

我们知道，主线程是线性运行的，这就导致了一个被发送的`BroadcastIntent`不可能同时被多个`Receiver`接受，我们无法预测到底哪个`Receiver`会首先做出响应，这种过程被称为无序`BroadcastIntent`通信。虽然不能在理论上实现并行，但是我们可以使用有序`BroadcastIntent`双向通信来规定`Receiver`接受的顺序，从而在一定程度上解决该弊端。

修改`VisibleFragment`类，告诉`SHOW_NOTIFICATION`的发送方如何处置该通知消息：

```java
public abstract class VisibleFragment extends Fragment {
    // ...
    private BroadcaseReceiver = mOnShowNotification = new BroadcastReceiver(){
        @Override public void onReceive(Context context,Intent intent){
            Log.i(TAG,"Cancel notification.");
            setResultCode(Activity.RESULT_CANCELED);
        }
    }
	// ...
}
```

在`PollService`服务中有序发送`BroadcastIntent`：

```java
public class PollService extends IntentService {
    // ...
    public static final String REQUEST_CODE = "REQUEST_CODE";
    public static final String NOTIFICATION = "NOTIFICATION";
    // ...
    @Override protected void onHandleIntent(Intent intent){
        // ..
        if(items.size() == 0){
            return;
        }else{
            String resultId = items.get(0).getId();
            if(resultId.equals(lastResultId)){
                // ...
            }else{
                // ...
                Notification notification = new NotificationCompat.Builder(this)
                        .setTicker(resources.getString(R.string.new_pictures_title))
                        .setSmallIcon(android.R.drawable.ic_menu_report_image)
                        .setContentTitle(resources.getString(R.string.new_pictures_text))
                        .setContentText(resources.getText(R.string.new_pictures_text))
                        .setContentIntent(pendingIntent)
                        .setAutoCancel(true)
                        .build();
                showBackgroundNotification(0,notification);
            }
            QueryPreferences.setLastResultId(this,resultId);
        }
    }
    private void showBackgroundNotification(int requestCode,Notification notification){
        Intent intent = new Intent(ACTION_SHOW_NOTIFICATION);
        intent.putExtra(REQUEST_CODE,requestCode).putExtra(NOTIFICATION,notification);
        sendOrderedBroadcast(
                intent, // sendBroadcast(Intent)
                PERM_PRIVATE, //sendBroadcast(String)
                null, // result receiver
                null, // 支持result receiver和Handler
                Activity.RESULT_OK, // 结果代码初始值
                null, // 结果数据
                null // 有序broadcast的结果附加内容
        );
    }
    // ...
}
```

创建一个用于接收的类：

```java
public class NotificationReceiver extends BroadcastReceiver {
    private static final String TAG = "NotificationReceiver";
    @Override public void onReceive(Context context, Intent intent){
        Log.i(TAG,"received result: " + getResultCode());
        if (getResultCode() != Activity.RESULT_OK){
            // A foreground activity cancelled the broadcast
            return;
        }
        int requestCode = intent.getIntExtra(PollService.REQUEST_CODE,0);
        Notification notification = (Notification) intent.getParcelableExtra(PollService.NOTIFICATION);
        NotificationManagerCompat notificationManager = NotificationManagerCompat.from(context);
        notificationManager.notify(requestCode,notification);
    }
}
```

```xml
<!-- AndroidManifest.xml -->
<manifest>
	<!-- ... -->
    <application>
    	<!-- ... -->
        <receiver android:name=".NotificationReceiver"
                  android:exported:"false">
        	<intent-filter android:priority="-999">
            	<action android:name="com.example.photogallery.SHOW_NOTIFICATION"/>
            </intent-filter>
        </receiver>
    </application>
</manifest>
```

### §1.5.14 `WebView`

下面通过`WebView`实现点击图片跳转至对应页面的效果。

注意到API返回的JSON结果中并没有直接给出链接，这需要我们手动生成链接：

```java
public class GalleryItem{
    // ...
    private String mOwner;
    // ...
    public String getOwner(){
        return mOwner;
    }
    public void setOwner(String owner){
        mOwner = owner
    }
    public Uri getPhotoPageUri(){
        return Uri.parse("https://www.flickr.com/photos")
            .buildUpon()
            .appendPath(mOwner)
            .appendPath(mId)
            .build();
    }
}
```

```java
public class FlickrFetchr {
    // ...
    private void parseItems(List<GalleryItem> items,JSONObject jsonBody) throws IOException,JSONException{
        // ...
        for(int i=0;i<photoJsonArray.length();i++){
            // ...
            if(!photoJsonObject.has("url_s")){
                continue;
            }else{
                item.setUrl(photoJsonObject.getString("url_s"));
                item.setOwner(photoJsonObject.getString("owner"));
            }
            items.add(item);
        }
    }
    // ...
}
```

```java
public class PhotoGalleryFragment extends VisibleFragment {
    // ...
    private class PhotoHolder extends RecyclerView.ViewHolder implements View.OnClickListener {
        // ...
        private GalleryItem mGalleryItem;
        public PhotoHolder(View itemView){
            super(itemView);
            mItemImageView = (ImageView) itemView.findViewById(R.id.item_image_view);
            itemView.setOnClickListener(this);
        }
        // ...
        public void bindGalleryItem(GalleryItem galleryItem){
            mGalleryItem = galleryItem;
        }
        @Override public void onClick(View v){
            Intent intent = new Intent(Intent.ACTION_VIEW,mGalleryItem.getPhotoPageUri());
            startActivity(intent);
        }
    }
    public class PhotoAdapter extends RecyclerView.Adapter<PhotoHolder>{
        // ...
        @Override public void onBindViewHolder(PhotoHolder photoHolder,int position){
            photoHolder.bindGalleryItem(galleryItem);
            // ...
        }
        // ...
    }
    // ...
}
```

这种弹出浏览器的方式虽然简单，但是操作体验不好，接下来我们用`WebView`实现内嵌网页。

新建包含`WebView`的XML布局文件：

```xml
<!-- fragment_photo_page.xml -->
<?xml version="1.0" encoding="utf-8"?>
<androidx.constraintlayout.widget.ConstraintLayout xmlns:android="http://schemas.android.com/apk/res/android"
    xmlns:app="http://schemas.android.com/apk/res-auto"
    xmlns:tools="http://schemas.android.com/tools"
    android:layout_width="match_parent"
    android:layout_height="match_parent">

    <WebView
        android:id="@+id/web_view"
        android:layout_width="409dp"
        android:layout_height="729dp"
        app:layout_constraintBottom_toBottomOf="parent"
        app:layout_constraintEnd_toEndOf="parent"
        app:layout_constraintStart_toStartOf="parent"
        app:layout_constraintTop_toTopOf="parent" />
</androidx.constraintlayout.widget.ConstraintLayout>
```

添加对应的`PhotoPageActivity`类和`PhotoPageFragment`类：

```java
public class PhotoPageFragment extends VisibleFragment{
    private static final String ARG_URI = "photo_page_url";
    private Uri mUri;
    private WebView mWebView;
    public static PhotoPageFragment newInstance(Uri uri){
        Bundle args = new Bundle();
        args.putParcelable(ARG_URI,uri);
        PhotoPageFragment fragment = new PhotoPageFragment();
        fragment.setArguments(args);
        return fragment;
    }
    @Override public void onCreate(Bundle savedInstanceState){
        super.onCreate(savedInstanceState);
        mUri = getArguments().getParcelable(ARG_URI);
    }
    @Override public View onCreateView(LayoutInflater inflater, ViewGroup container, Bundle savedInstanceState){
        View v = inflater.inflate(R.layout.fragment_photo_page,container,false);
        mWebView = (WebView) v.findViewById(R.id.web_view);
        return v;
    }
}
```

```java
public class PhotoPageActivity extends SingleFragmentActivity{
    public static Intent newIntent(Context context, Uri photoPageUri){
        Intent intent = new Intent(context,PhotoPageActivity.class);
        intent.setData(photoPageUri);
        return intent;
    }
    @Override protected Fragment createFragment(){
        return PhotoPageFragment.newInstance(getIntent().getData());
    }
}
```

回到`PhotoGalleryFragment`类，弃用原来的隐式`intent`，改用新建的`Activity`：

```java
public class PhotoGalleryFragment extends VisibleFragment {
    // ...
    private class PhotoHolder extends RecyclerView.ViewHolder implements View.onClickListener{
        // ...
        @Override public void onClick(View v){
            /*  弃用隐式intent
             *  Intent intnet = new Intent(
             *  	Intent.ACTION_VIEW,
             *		mGalleryItem.getPhotoPageUri()
             *	);
            */
            Intent intent = PhotoPageActivity.newIntent(
            	getActivity(),
                mGalleryItem.getPhotoPageUri()
            );
            startActivity(intent);
        }
    }
    // ...
}
```

然后在`AndroidManifest.xml`中声明新建的`Activity`：

```xml
<manifest>
	<!-- ... -->
    <application>
        <!-- ... -->
		<activity android:name=".PhotoPageActivity"/>
        <!-- ... -->
    </application>
</manifest>
```

要让`WebView`正常显示网页，必须满足以下条件：

- 告诉`WebView`要打开的URL
- 启用`JavaScript`，使用`@SuppressLint("setJavaScriptEnabled")`来忽略Android Lint的警告。

```java
public class PhotoPageFragment extends VisibleFragment {
    // ...
    @Override public View onCreateView(LayoutInflater inflater,ViewGroup container,Bundle savedInstanceState){
        View v = inflater.inflate(R.layout.fragment_photo_page,container,false);
        mWebView = (WebView) v.findViewById(R.id.web_view);
        mWebView.getSettings().setJavaScriptEnabled(true);
        mWebView.setWebViewClient(new WebViewClient());
        mWebView.loadUrl(mUri.toString());
        return v;
    }
}
```

接着对`WebView`进行美化，设置加载进度条样式：

```java
public class PhotoPageFragment extends VisibleFragment {
    // ...
    private ProgressBar mProgressBar;
    // ...
    @Override public View onCreateView(LayputInflater inflater,ViewGroup container,Bundle savedInstanceState){
        // ...
        mProgressBar = (Progress) v.findViewById(R.id.progress_bar);
        mProgressBar.setMax(100);
        mWebView.setWebChromeClient(new WebChromeClient(){
            public void onProgressChanged(WebView webView,int newProgress){
                if (newProgress == 100){
                    mProgressBar.setVisibility(View.GONE);
                }else{
                    mProgressBar.setVisibility(View.VISIBLE);
                    mProgressBar.setProgress(newProgress);
                }
            }
            public void onReceivedTitle(WebView webView,String title){
                AppCompatActivity appCompatActivity = (AppCompatActivity) getActivity();
                appCompatActivity.getSupportActionBar().setSubtitle(title);
            }
        })
    }
}
```

旋转屏幕时，`PhotoPageFragment`会销毁重建，导致该视图结构中的`WebView`会刷新加载。Android文档推荐让`Activity`自己处理设备配置变更，只需要在`AndroidManifest.xml`中添加如下配置信息：

```xml
<manifest>
	<!-- ... -->
    <application>
    	<!-- ... -->
        <activity
                  android:name=".PhotoPageActivity"
                  android:configChanges="keyboardHidden|orientation|screenSize"/>
        <!-- ... -->
    </application>
</manifest>
```

### §1.5.15 注入JavaScript

`WebView`可以使用以下方法向页面注入JavaScript对象：

```java
mWebView.addJavascriptInterface(
    new Object(){
        @JavascriptInterface public void TestFunction(String message){
            Log.i(TAG,"Received message from JavaScript: " + message);
        }
    },
    "TestObject"
);
```

在HTML中可以调用：

```html
<script type="text/javascript">
	TestObject.TestFunction("Hello World!");
</script>
```

# §3 日志与调试

## §3.1 启用日志

Android的`android.util.Log`用于向系统及共享日志中心发送日志信息，内含多种方法，分别代表不同的等级：

| 方法                           | 日志级别 | 说明                   |
| ------------------------------ | -------- | ---------------------- |
| `Log.e(String tag,String msg)` | ERROR    | 错误                   |
| `Log.w(String tag,String msg)` | WARNING  | 警告                   |
| `Log.i(String tag,String msg)` | INFO     | 信息型消息             |
| `Log.d(String tag,String msg)` | DEBUG    | 调试输出(可能被过滤掉) |
| `Log.v(String tag,String msg)` | VERBOSE  | 仅用于开发             |

常用其中的`Log.d(String tag, String msg)`方法，其中`tag`是日志的来源，第二个是日志的具体内容。

```java
public class MainActivity extends AppCompatActivity {
	// ...
	private static final String TAG = "MainActivity";
    @Override protected void onCreate(Bundle savedInstanceState) {
    	super.onCreate(savedInstanceState);
        Log.d(TAG,"onCreate(Bundle) called");
        //...
    }
    @Override public void onStart(){
        super.onStart();
        Log.d(TAG,"onStart() called");
    }
    @Override public void onResume(){
        super.onResume();
        Log.d(TAG,"onResume() called");
    }
    @Override public void onPause(){
        super.onPause();
        Log.d(TAG,"onPause() called");
    }
    @Override public void onStop(){
        super.onStop();
        Log.d(TAG,"onStop() called");
    }
    @Override public void onDestroy(){
        super.onDestroy();
        Log.d(TAG,"onDestroy() called");
    }
    // ...
}
```

在Logcat中可以看到如下信息：

```Logcat
// 应用被创建时,从不存在状态变为存在状态
2022-01-20 14:01:32.591 6937-6937/com.example.geoquiz I/art:     at void com.example.geoquiz.MainActivity.onCreate(android.os.Bundle) (MainActivity.java:32)
2022-01-20 14:01:32.623 6937-6937/com.example.geoquiz D/MainActivity: onStart() called
2022-01-20 14:01:32.624 6937-6937/com.example.geoquiz D/MainActivity: onResume() called
// 单击返回键时,从运行状态变为不存在状态
2022-01-20 14:02:12.239 6937-6937/com.example.geoquiz D/MainActivity: onPause() called
2022-01-20 14:02:12.394 6937-6937/com.example.geoquiz D/MainActivity: onStop() called
2022-01-20 14:02:12.394 6937-6937/com.example.geoquiz D/MainActivity: onDestroy() called
// 单击Home键时,从运行状态变为停止状态
2022-01-20 14:05:32.196 7076-7076/com.example.geoquiz D/MainActivity: onPause() called
2022-01-20 14:05:32.360 7076-7076/com.example.geoquiz D/MainActivity: onStop() called
// 旋转屏幕时
2022-01-20 14:08:54.998 7183-7183/com.example.geoquiz D/MainActivity: onPause() called
2022-01-20 14:08:55.000 7183-7183/com.example.geoquiz D/MainActivity: onStop() called
2022-01-20 14:08:55.001 7183-7183/com.example.geoquiz D/MainActivity: onDestroy() called
2022-01-20 14:08:55.058 7183-7183/com.example.geoquiz D/MainActivity: onCreate(Bundle) called
2022-01-20 14:08:55.067 7183-7183/com.example.geoquiz D/MainActivity: onStart() called
2022-01-20 14:08:55.068 7183-7183/com.example.geoquiz D/MainActivity: onResume() called
```

## §3.2 审查异常

假设删去了`.java`文件中的某一行，发现APP闪退,如何根据日志判断出问题在哪？

```log
E/AndroidRuntime: FATAL EXCEPTION: main
    Process: com.example.geoquiz, PID: 3296
    java.lang.RuntimeException: Unable to start activity ComponentInfo{com.example.geoquiz/com.example.geoquiz.MainActivity}: java.lang.NullPointerException: Attempt to invoke virtual method 'void android.widget.TextView.setText(int)' on a null object reference
        at android.app.ActivityThread.performLaunchActivity(ActivityThread.java:2670)
        at android.app.ActivityThread.handleLaunchActivity(ActivityThread.java:2731)
        at android.app.ActivityThread.-wrap12(ActivityThread.java)
        at android.app.ActivityThread$H.handleMessage(ActivityThread.java:1482)
        at android.os.Handler.dispatchMessage(Handler.java:102)
        at android.os.Looper.loop(Looper.java:154)
        at android.app.ActivityThread.main(ActivityThread.java:6161)
        at java.lang.reflect.Method.invoke(Native Method)
        at com.android.internal.os.ZygoteInit$MethodAndArgsCaller.run(ZygoteInit.java:892)
        at com.android.internal.os.ZygoteInit.main(ZygoteInit.java:782)
     Caused by: java.lang.NullPointerException: Attempt to invoke virtual method 'void android.widget.TextView.setText(int)' on a null object reference
        at com.example.geoquiz.MainActivity.updateQuestion(MainActivity.java:97)
        at com.example.geoquiz.MainActivity.onCreate(MainActivity.java:40)
        at android.app.Activity.performCreate(Activity.java:6698)
        at android.app.Instrumentation.callActivityOnCreate(Instrumentation.java:1118)
        at android.app.ActivityThread.performLaunchActivity(ActivityThread.java:2623)
        at android.app.ActivityThread.handleLaunchActivity(ActivityThread.java:2731) 
        at android.app.ActivityThread.-wrap12(ActivityThread.java) 
        at android.app.ActivityThread$H.handleMessage(ActivityThread.java:1482) 
        at android.os.Handler.dispatchMessage(Handler.java:102) 
        at android.os.Looper.loop(Looper.java:154) 
        at android.app.ActivityThread.main(ActivityThread.java:6161) 
        at java.lang.reflect.Method.invoke(Native Method) 
        at com.android.internal.os.ZygoteInit$MethodAndArgsCaller.run(ZygoteInit.java:892) 
        at com.android.internal.os.ZygoteInit.main(ZygoteInit.java:782) 
```

- `Attempt to invoke virtual method 'void android.widget.TextView.setText(int)' on a null object reference`

  某个函数在调用`TextView.setText()`方法时，该`TextView`实例不存在。

- `at android.app.ActivityThread.performLaunchActivity(ActivityThread.java:2670)`

  这是一个运行时错误，在编译过程中无法发现。

- `at com.example.geoquiz.MainActivity.updateQuestion(MainActivity.java:97)`

  我们定位到出错的这个函数体：

  ```java
  private void updateQuestion(){
  	int question = mQuestionBank[mCurrentIndex].getTextResId();
  	mQuestionTextView.setText(question);
  }
  ```

  发现是`mQuestionTextView`是空指针。我们再定位到该变量被定义的地方：

  ```java
  private TextView mQuestionTextView;
  ```

  于是我们找到了问题：只定义了`mQuestionTextView`，而没有给它赋值，因此缺的那一行就是：

  ```java
  mQuestionTextView = (TextView) findViewById(R.id.question_text_view);
  ```

## §3.3 栈跟踪日志

假设删去了`.java`文件中的某一行，发现程序虽然能运行，但是点击Next按钮无法跳转到下一个Quiz，如何根据日志判断出问题在哪？

我们先看Logcat，但是发现除了预先设定的`Log.d()`输出的日志外，没有报错信息：

```log
2022-01-21 11:38:37.655 3578-3578/com.example.geoquiz D/MainActivity: onCreate(Bundle) called
2022-01-21 11:38:37.663 3578-3578/com.example.geoquiz I/art:     at void com.example.geoquiz.MainActivity.onCreate(android.os.Bundle) (MainActivity.java:33)
2022-01-21 11:38:37.663 3578-3578/com.example.geoquiz I/art:     at void com.example.geoquiz.MainActivity.onCreate(android.os.Bundle) (MainActivity.java:33)
2022-01-21 11:38:37.697 3578-3578/com.example.geoquiz D/MainActivity: onStart() called
2022-01-21 11:38:37.698 3578-3578/com.example.geoquiz D/MainActivity: onResume() called
```

这意味着该BUG不是在编译时和运行时产生的低级BUG，而是高层逻辑上的BUG，这时我们在§3.2中使用的日志不足以满足我们的调试需求。因此我们还需要使用更多的`Log.d()`来记录栈跟踪日志，观察每次点击Next按钮后，`mCurrentIndex`变量的变化情况：

```java
public class MainActivity extends AppCompatActivity{
    // ...
    private void updateQuestion(){
        Log.d(TAG,"Updating question text ",new Exception());
        //...
    }
}
```

这里我们给`Log.d()`将一个新建的`Exception`对象传入了新形参`Throwable tr`当中，用于作为不抛出的`Exception`实例传入`updateQuestion()`方法中，从而输出该`Exception`的栈跟踪记录：

```log
2022-01-21 11:49:56.739 3805-3805/com.example.geoquiz D/MainActivity: Updating question text 
    java.lang.Exception
        at com.example.geoquiz.MainActivity.updateQuestion(MainActivity.java:96)
        at com.example.geoquiz.MainActivity.access$300(MainActivity.java:11)
        at com.example.geoquiz.MainActivity$3.onClick(MainActivity.java:60)
        // ...
2022-01-21 11:49:57.730 3805-3805/com.example.geoquiz D/MainActivity: Updating question text 
    java.lang.Exception
        at com.example.geoquiz.MainActivity.updateQuestion(MainActivity.java:96)
        at com.example.geoquiz.MainActivity.access$300(MainActivity.java:11)
        at com.example.geoquiz.MainActivity$3.onClick(MainActivity.java:60)
        // ...
```

可以看到，程序的确调用了`MainActivity.updateQuestion()`方法，刷新了Quiz，所以只可能是因为`mCurrentIndex`的值没有改变。向上跟踪到`MainActivity.onClick()`，果然没有该变量的更新语句，于是只需增添上即可：

```java
mCurrentIndex = (mCurrentIndex + 1) % mQuestionBank.length;
```

## §3.4 设置断点

虽然日志可以方便的追踪栈，但是每次输出的文本太长了，会让Logcat不清晰，并且黑客可以通过输出的调试信息来绕过类文件，直接得到程序内部的结构。基于此，利用断点进行调试更加灵活和安全。

Android Studio支持的断点有六种类型：

- Exception Breakpoints
- Symbolic Breakpoints
- Java Method Breakpoints
- Java Field Watchpoints
- Java Exception Breakpoints
- Kotlin Filed Watchpoints

## §3.5 Android Lint

Android Lint是Android应用代码的静态分析器，能在不运行代码的情况下检查代码错误。在Android Studio的菜单栏`Analyse/Inspect Code...`可以使用，然后在底边的`Inspection Results`查看结果。

项目如果在低版本SDK中引用了高版本SDK才引入的方法，那么在低版本SDK上运行时就会崩溃，一般会抛出空指针错误，在测试过程中非常耗时。得益于Android Lint的改进，现在开发者可以使用该工具，自动检查API和`build.gradle`中的配置是否发生冲突。

# §4 `Activity`

## §4.1 `Launcher Activity`

`Launcher Activity`是指应用被创建时第一个运行的`Activity`，`AndroidManifest.xml`中，不仅涵盖了整个项目中所有使用的`Activity`，并且使用`<action>`和`<category>`标签指定了谁是`Launcher Activity`：

```xml
<?xml version="1.0" encoding="utf-8"?>
<manifest xmlns:android="http://schemas.android.com/apk/res/android"
    package="com.example.geoquiz">
    <application
        android:allowBackup="true"
        android:icon="@mipmap/ic_launcher"
        android:label="@string/app_name"
        android:roundIcon="@mipmap/ic_launcher_round"
        android:supportsRtl="true"
        android:theme="@style/Theme.GeoQuiz">
        
        <activity
            android:name=".CheatActivity"
            android:exported="false" />
        <!-- Launcher Activity -->
        <activity android:name=".MainActivity">
            <!-- 定义Launcher Activity的代码 -->
            <intent-filter>
                <action android:name="android.intent.action.MAIN" />
                <category android:name="android.intent.category.LAUNCHER" />
            </intent-filter>
        </activity>
    </application>
</manifest>
```

## §4.2 切换`Activity`

入栈：

- `startActivity(Intent intent)`
- `startActivityForResult(Intent intent,int requestCode)`

出栈：

- 用户按下返回键
- `Activity.finish()`

# §5 兼容性

## §5.1 编译配置

在项目的`./app/`目录下有一个`build.gradle`文件，记录着当前项目的编译配置：

```gradle
plugins {
    id 'com.android.application'
}

android {
    compileSdkVersion 30
    buildToolsVersion '30.0.3'

    defaultConfig {
        applicationId "com.example.geoquiz"
        minSdkVersion 30
        targetSdkVersion 30
        versionCode 1
        versionName "1.0"

        testInstrumentationRunner "androidx.test.runner.AndroidJUnitRunner"
    }

    buildTypes {
        release {
            minifyEnabled false
            proguardFiles getDefaultProguardFile('proguard-android-optimize.txt'), 'proguard-rules.pro'
        }
    }
    compileOptions {
        sourceCompatibility JavaVersion.VERSION_1_8
        targetCompatibility JavaVersion.VERSION_1_8
    }
}

dependencies {

    implementation 'androidx.appcompat:appcompat:1.1.0'
    implementation 'com.google.android.material:material:1.1.0'
    implementation 'androidx.constraintlayout:constraintlayout:1.1.3'
    testImplementation 'junit:junit:4.+'
    androidTestImplementation 'androidx.test.ext:junit:1.1.1'
    androidTestImplementation 'androidx.test.espresso:espresso-core:3.2.0'
}
```

其中有一些特别重要的参数：

- `compileSdkVersion`：编译版本，开发者和编译器内的共享信息，不会传给Android系统。IDE和编译器根据`compileSdkVersion`查找所需的类和包
- `minSdkVersion`：最低支持版本，该APP会拒绝安装在比`minSdkVersion`更低的版本上。
- `targetSdkVersion`：目标版本，告知Android该APP是为`targetSdkVersion`版本的API设计的。

手动修改`build.gradle`后，必须要点击Android Studio的菜单栏`Tools/Android/Sync Project with Gradle Files`，实现项目和Gradle的同步，项目随即会重新编译。

## §5.2 检查编译版本

前面我们提到过，可以更改`build.gradle`来限制API版本，也可以用Android Lint提前发现兼容性问题。然而这些方法只是回避了兼容性问题，都没有真正的解决。我们的目标是让这个项目在哪个API版本的Android系统上都能跑，只不过高版本系统可以使用更多的功能，而低版本系统在牺牲部分功能的情况下仍然能进行基本的使用。为此，我们可以利用`Build.VERSION.SDK_INT`获取当前系统的API等级，利用`Build.VERSION_CODES.xxx`获取某安卓代号对应的API等级，将高级别API代码放在判断系统版本的条件语句中：

```java
// 给mShowAnswerButton增加圆形收缩消失动画
import android.animation.Animator;
import android.animation.AnimatorListenerAdapter;
// ...
public class CheatActivity extends AppCompatActivity{
    @Override protected void onCreate(Bundle savedInstanceState){
        // ...
        mShowAnswerButton.setOnClickListener(new View.OnClickListener{
            @Override public void onClick(View v){
                // ...
                if(Build.VERSION.SDK_INT >= Build.VERSION_CODES.LOLLIPOP){
                    int cx = mShowAnswerButton.getWidth() / 2;
                    int cy = mShowAnswerButton.getHeight() / 2;
                    float radius = mShowAnswerButton.getWidth();
                    Animator anim = ViewAnimationUtils.createCircularReveal(
                            mShowAnswerButton, cx, cy, radius, 0);
                    anim.addListener(new AnimatorListenerAdapter() {
                        @Override public void onAnimationEnd(Animator animation) {
                            super.onAnimationEnd(animation);
                            mShowAnswerButton.setVisibility(View.INVISIBLE);
                        }
                    });
                    anim.start();
                }else{
                    mShowAnswerButton.setVisibility(View.INVISIBLE);
                }
            }
        });
    }
}
```

## §5.3 Android开发者文档

[Android开发者文档](http://developer.android.com/)分为三大部分：设计，开发和发布，可以根据API版本进行筛选。

