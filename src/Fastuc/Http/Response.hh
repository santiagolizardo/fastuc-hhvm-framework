<?hh // strict
namespace Fastuc\Http;

class Response
{
	/**
	 * @var array
	 */
	private static Map $statusCodes = ImmMap {
		100 => 'Continue',
		101 => 'Switching Protocols',
		102 => 'Processing',
		200 => 'OK',
		201 => 'Created',
		202 => 'Accepted',
		203 => 'Non-Authoritative Information',
		204 => 'No Content',
		205 => 'Reset Content',
		206 => 'Partial Content',
		207 => 'Multi-Status',
		208 => 'Already Reported',
		226 => 'IM Used',
		300 => 'Multiple Choices',
		301 => 'Moved Permanently',
		302 => 'Found',
		303 => 'See Other',
		304 => 'Not Modified',
		305 => 'Use Proxy',
		306 => 'Reserved',
		307 => 'Temporary Redirect',
		308 => 'Permanent Redirect',
		400 => 'Bad Request',
		401 => 'Unauthorized',
		402 => 'Payment Required',
		403 => 'Forbidden',
		404 => 'Not Found',
		405 => 'Method Not Allowed',
		406 => 'Not Acceptable',
		407 => 'Proxy Authentication Required',
		408 => 'Request Timeout',
		409 => 'Conflict',
		410 => 'Gone',
		411 => 'Length Required',
		412 => 'Precondition Failed',
		413 => 'Request Entity Too Large',
		414 => 'Request-URI Too Long',
		415 => 'Unsupported Media Type',
		416 => 'Requested Range Not Satisfiable',
		417 => 'Expectation Failed',
		422 => 'Unprocessable Entity',
		423 => 'Locked',
		424 => 'Failed Dependency',
		425 => 'Unassigned',
		426 => 'Upgrade Required',
		427 => 'Unassigned',
		428 => 'Precondition Required',
		429 => 'Too Many Requests',
		430 => 'Unassigned',
		431 => 'Request Header Fields Too Large',
		500 => 'Internal Server Error',
		501 => 'Not Implemented',
		502 => 'Bad Gateway',
		503 => 'Service Unavailable',
		504 => 'Gateway Timeout',
		505 => 'HTTP Version Not Supported',
		506 => 'Variant Also Negotiates (Experimental)',
		507 => 'Insufficient Storage',
		508 => 'Loop Detected',
		509 => 'Unassigned',
		510 => 'Not Extended',
		511 => 'Network Authentication Required',	
	};

	/**
	 * @return array Returns a list of all known HTTP status codes.
	 */
	public static function getStatusCodes() : ImmMap
	{
		return self::$statusCodes;
	}

	private Map<string, string> $headers;

	/**
	 * @var string
	 */
	private string $body;

	/**
	 * @var integer
	 */
	private int $statusCode;

	public function __construct()
	{
		$this->headers = new Map<string, string>();
		$this->body = '';
		$this->statusCode = 200;
	}

	/**
	 * @param string $contentType
	 */
	public function setContentType( string $contentType ) : void
	{
		$this->addHeader( 'Content-Type', $contentType );
	}

	/**
	 * @param string $type
	 * @param string $fileName
	 */
	public function setContentDisposition( string $type, string $fileName ) : void
	{
		$this->addHeader( 'Content-Disposition', "$type; filename=\"$fileName\"" );
	}

	/**
	 * @param string $key
	 * @param string $value
	 */
	public function addHeader( string $key, string $value ) : void
	{
		$this->headers[ $key ] = $value;
	}

	/**
	 * @param integer $errorCode
	 * @throws \InvalidArgumentException
	 */
	public function setStatusCode( int $statusCode ) : void
	{
		if( !isset( self::$statusCodes[ $statusCode ] ) )
		{
			throw new \InvalidArgumentException( 'Invalid HTTP status code: ' . $statusCode );
		}

		$this->statusCode = $statusCode;
	}

	/**
	 * @return integer
	 */
	public function getStatusCode() : int
	{
		return $this->statusCode;
	}

	/**
	 * @param string $body
	 */
	public function setBody( string $body ) : void
	{
		$this->body = $body;
	}

	/**
	 * @return string
	 */
	public function getBody() : string
	{
		return $this->body;
	}

	/**
	 * Sends all the headers and body back to the client.
	 */
	public function send() : void
	{
		$header = implode( ' ', array( $_SERVER['SERVER_PROTOCOL'], $this->statusCode, self::$statusCodes[ $this->statusCode ] ) );
		$this->sendHeader( $header, true, $this->statusCode );

		foreach( $this->headers as $name => $value )
		{
			$this->sendHeader( $name . ': ' . $value );
		}

		$this->write( $this->body );
	}

	public function sendHeader( string $header, bool $replace = true, int $statusCode = null ) : void
	{
		header( $header, $replace, $statusCode );
	}

	public function write( string $text ) : void
	{
		echo $text;
	}
}

