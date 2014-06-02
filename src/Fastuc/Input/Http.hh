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
		$this->method = strtoupper( $method );

		switch( $this->method )
		{
			case 'HEAD':
			case 'GET':
			case 'DELETE':
				$this->params = $_GET;
				break;
			case 'POST':
				$this->params = $_POST;
				break;
			case 'PUT':
				parse_str( file_get_contents( 'php://input' ), $this->params );
				break;
			case 'REQUEST':
				$this->params = $_REQUEST;
				break;
			// @TODO: Remove 'CUSTOM'. It shouldn't be here.
			case 'CUSTOM':
				$this->params = array();
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

