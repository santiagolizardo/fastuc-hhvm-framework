<?hh // strict
namespace Fastuc\Input;

class Http extends \Fastuc\Utils\TypedArray
{
	/**
	 * @var string
	 */
	private string $method;

	/**
	 * @param string $method
	 */
	public function __construct( string $method )
	{
		parent::__construct();

		$this->method = strtoupper( $method );

		switch( $this->method )
		{
			case 'GET':
				$this->params = new Map<string, mixed>( $_GET );
				break;
			case 'POST':
				$this->params = new Map<string, mixed>( $_POST );
				break;
			case 'PUT':
				parse_str( file_get_contents( 'php://input' ), $this->params );
				break;
			case 'REQUEST':
				$this->params = new Map<sting, mixed>( $_REQUEST );
				break;
			case 'DELETE':
			case 'OPTIONS':
			case 'HEAD':
			case 'CUSTOM':
				break;
			default:
				throw new \InvalidArgumentException( "Method \"$method\" is invalid" );
		}
	}

	/**
	 * @return string
	 */
	public function getMethod() : string
	{
		return $this->method;
	}
}

