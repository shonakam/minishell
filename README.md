# MINISHELL

## 戦略

### PHASE[0]: INIT_ENVIRONMENT
このフェーズでは、シェルの初期化を行います。
- **環境変数の取得と管理**:
  - `make_envlist` 関数を使用して、環境変数をリストに変換します。
  - `getenv` 関数を使用して `PATH` 環境変数を取得し、コマンド検索に使用します。
- **プロンプト表示**:
  - ユーザーにコマンド入力を促すプロンプトを表示します。
- **リソースの初期化**:
  - 必要なデータ構造やリソースを初期化します。

### PHASE[1]: CLI_INPUT > TOKENIZE > COMMANDOIZATION
このフェーズでは、ユーザーからのコマンド入力を処理し、実行可能なコマンドに変換します。
- **CLI入力の取得**:
  - `readline` 関数を使用して、ユーザーからコマンドライン入力を取得します。
  - 入力が空でない場合は履歴に追加します。
- **トークナイズ**:
  - 入力されたコマンドラインをトークンに分割します（`ft_lexer` 関数を使用）。
- **コマンドの構築**:
  - トークンからコマンド構造体を構築します（`build_commands` 関数を使用）。
  - 各トークンに基づいてコマンドや引数を設定し、リダイレクトやパイプ処理を設定します。
    - コマンド構築の過程で、パイプ (|) が検出されるたびに新しい cmd 構造体を生成します。<br>これにより、1つのパイプライン内で複数のコマンドを分離します。

### PHASE[2]: COMMAND_EXECUTION
このフェーズでは、構築されたコマンドを実行します。
- **コマンドの検証**:
  - `PATH` 環境変数を使用してコマンドのフルパスを検索します。
  - `access` 関数を使用して、コマンドが実行可能であるか確認します。
- **コマンドの実行**:
  - `execve` 関数を使用してコマンドを実行します。
  - 実行する前に、必要なファイルディスクリプタ（標準入力、標準出力、標準エラー）を設定します。
- **エラーハンドリング**:
  - コマンドが見つからない場合や実行失敗の場合はエラーメッセージを表示します。

### PHASE[3]: CLEANUP | EXIT
コマンド実行後のクリーンアップ処理を行います。
- **リソースの解放**:
  - コマンドやトークン、環境変数リストなどのメモリを解放します（`free_commands` や `free_tokens` など）。
- **プロンプトの再表示**:
  - クリーンアップ後に再びプロンプトを表示し、新しいコマンドの入力を待ちます。

