<?hh // strict
namespace Fastuc\Services;

class Akismet
{
	/**
	 * @var string
	 */
	private $key;

	/**
	 * @var string
	 */
	private $blog;

	/**
	 * @var string
	 */
	private $userIp;

	/**
	 * @var string
	 */
	private $commentType;

	/**
	 * @var string
	 */
	private $referer;

	/**
	 * @var string
	 */
	private $userAgent;

	/**
	 * @param string $key
	 * @param string $blog
	 */
	public function __construct( $key, $blog )
	{
		$this->key = $key;
		$this->blog = $blog;
		
		$server = new \Fastuc\Input\Server();
		$this->userIp = $server->getString( 'REMOTE_ADDR' );
		$this->referer = $server->getString( 'HTTP_REFERER' );
		$this->userAgent = $server->getString( 'HTTP_USER_AGENT' );
		$this->commentType = 'comment';
	}

	/**
	 * @return bool
	 */
	public function validKey()
	{	
		$curl = curl_init();

		curl_setopt_array($curl, array(
		CURLOPT_RETURNTRANSFER => 1,
		CURLOPT_URL => 'rest.akismet.com/1.1/verify-key',
		CURLOPT_USERAGENT => 'WordPress/3.1.1 | Akismet/2.5.3',
		CURLOPT_POST => 1,
		CURLOPT_POSTFIELDS => array(
			'key' => $this->key,
			'blog' => $this->blog
			)
		));

		$resp = curl_exec($curl);
		curl_close($curl);
		
		return ( 'valid' === $resp );
	}

	/**
	 * @param string $text
	 * @return bool
	 */
	public function isSpam( $text )
	{
		$comment['blog'] = $this->blog;
		$comment['user_ip'] = $this->userIp;
		$comment['user_agent'] = $this->userAgent;	
		$comment['referrer'] = $this->referer;
		$comment['comment_type'] = 'comment';
		$comment['comment_content'] = $text;
		
		$params = http_build_query( $comment );
		
		$curl = curl_init();
		
		curl_setopt_array($curl, array(
			CURLOPT_RETURNTRANSFER => true,
			CURLOPT_URL => $this->key . '.rest.akismet.com/1.1/comment-check',
			CURLOPT_USERAGENT => 'WordPress/3.1.1 | Akismet/2.5.3',
			CURLOPT_POST => 1,
			CURLOPT_POSTFIELDS => $params
		));
		
		$resp = curl_exec($curl);
		curl_close($curl);
		
		return ( 'true' === $resp );
	}
}

